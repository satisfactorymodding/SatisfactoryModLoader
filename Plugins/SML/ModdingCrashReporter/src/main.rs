use log::{error, info, warn};
use std::path::{PathBuf};
use std::{env, fs};
use std::io::Write;

use hyper::client::ResponseFuture;
use hyper::{Body, Client};
use hyper::header::CONTENT_TYPE;
use hyper::Request;

use rand::{thread_rng, Rng};
use rand::distributions::Alphanumeric;

#[tokio::main]
async fn main() {
	simple_logger::SimpleLogger::new().env().init().unwrap();

	info!("Satisfactory Modding Crash Reporter Launched!");

	let log_text = match read_log() {
		Some(log) => log,
		None => return,
	};

	let endpoints = get_endpoints();

	send_log_to_endpoints(&endpoints, &log_text).await;

	warn!("done!");
}

macro_rules! skip_fail {
	($res:expr) => {
		match $res {
			Ok(val) => val,
			Err(_) => {
				continue;
			}
		}
	};
}

fn get_endpoints() -> Vec<String> {
	let args: Vec<_> = std::env::args().collect();
	if args.len() < 3 {
		error!("No Mods-Path and/or SML-Config-Path Argument given!");
		return vec![];
	}
	let mods_path = PathBuf::from(&args[1]);
	let sml_config_path = PathBuf::from(&args[2]);

	let sml_config = std::fs::read_to_string(sml_config_path).expect("Failed to read SML config!");
	let sml_config = json::parse(&sml_config).expect("Failed to parse SML config!");
	let accepted_endpoints: Vec<_> = sml_config["acceptedCrashReportingEndpoints"].members().map(|endpoint| {
		match endpoint.as_str() {
			Some(str) => str,
			None => ""
		}
	}).filter(|endpoint| endpoint.len() > 0).collect();

	let mut endpoints = Vec::new();
	for entry in fs::read_dir(mods_path).expect("Invalid Mods folder path!") {
		let entry = skip_fail!(entry);
		if !skip_fail!(entry.file_type()).is_dir() {
			continue
		}
		let mod_name = entry.file_name().to_str().unwrap().to_owned();
		let plugin_path = entry
			.path()
			.join(entry.file_name())
			.with_extension("uplugin");
		let plugin_json = skip_fail!(std::fs::read_to_string(plugin_path));
		let plugin_descriptor = skip_fail!(json::parse(&plugin_json));
		let endpoint = &plugin_descriptor["CrashReporterEndpoint"];
		endpoints.push(match endpoint.as_str() {
			Some(str) => {
				if accepted_endpoints.contains(&str) {
					info!(
						"Found accepted endpoint '{}' for Mod '{}'",
						str,
						mod_name
					);
					String::from(str)
				} else {
					info!("Found rejected endpoint '{}' for Mod '{}'", str, mod_name);
					continue
				}
			}
			None => continue,
		});
	}

	endpoints
}

fn get_log_path() -> Option<PathBuf> {
	let key = "LOCALAPPDATA";
	match env::var_os(key) {
		Some(val) => Some(PathBuf::from(val).join("FactoryGame/Saved/Logs/FactoryGame.log")),
		None => {
			error!("Environment variable '{key}' is not defined.");
			None
		}
	}
}

fn read_log() -> Option<String> {
	match std::fs::read_to_string(get_log_path()?) {
		Ok(log) => Some(log),
		Err(_) => {
			error!("Should have been able to read the file");
			None
		}
	}
}

async fn send_log_to_endpoints(endpoints: &Vec<String>, log_text: &str) {
	let client = Client::builder().build(hyper_tls::HttpsConnector::new());

	let futures: Vec<ResponseFuture> = endpoints
		.iter()
		.map(|endpoint| {
			let request = create_request_for_endpoint(endpoint.as_str(), log_text);
			client.request(request)
		})
		.collect();

	let responses = futures::future::join_all(futures).await;
	for (i, response) in responses.iter().enumerate() {
		match response {
			Ok(_) => info!("Report successfully sent to: '{}'", endpoints[i]),
			Err(e) => warn!("Failed to send report to '{}'!\n{}", endpoints[i], e),
		}
	}
}

fn create_request_for_endpoint(endpoint: &str, log_text: &str) -> Request<Body> {
	match try_create_request_for_endpoint(endpoint, log_text) {
		Ok(req) => req,
		Err(_) => {
			Request::post(endpoint)
				.body(log_text.to_owned().into())
				.unwrap()
		}
	}
}

fn try_create_request_for_endpoint(endpoint: &str, log_text: &str) -> Result<Request<Body>, Box<dyn std::error::Error>> {
	let url = url::Url::parse(endpoint)?;
	if url.host_str().ok_or(simple_error::SimpleError::new(""))?.ends_with("discord.com") {
		let boundary: String = thread_rng()
			.sample_iter(&Alphanumeric)
			.take(30)
			.map(char::from)
			.collect();

		let mut body: Vec<u8> = Vec::new();
		write!(body, "--{}\r\n", boundary)?;
		write!(body, "Content-Disposition: form-data; name=\"payload_json\"\r\n")?;
		write!(body, "Content-Type: application/json\r\n\r\n")?;
		write!(body, "{}\r\n", json::object!{
			"attachments": [{
				"id": 0u64,
				"description": "A Satisfactory Log File after a Game Crash",
				"filename": "FactoryGame.log"
			}]
		}.dump())?;
		write!(body, "--{}\r\n", boundary)?;
		write!(body, "Content-Disposition: form-data; name=\"files[0]\"; filename=\"FactoryGame.log\"\r\n")?;
		write!(body, "Content-Type: text/plain\r\n\r\n")?;
		write!(body, "{}\r\n", log_text)?;
		write!(body, "--{}--\r\n", boundary)?;
		Ok(Request::post(endpoint)
			.header(CONTENT_TYPE, &*format!("multipart/form-data; boundary={}", boundary))
			.body(body.into())
			.unwrap())
	} else {
		Err(Box::new(simple_error::SimpleError::new("")))
	}
}
