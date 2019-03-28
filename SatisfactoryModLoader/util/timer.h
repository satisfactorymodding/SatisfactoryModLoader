#pragma once

class Timer {
	bool clear = false;

public:
	template<typename T>
	void setTimeout(T function, int delay);

	template<typename T>
	void setInterval(T function, int interval);
	void stop();
};