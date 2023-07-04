using System;
using System.Collections.Generic;

namespace AccessTransformers.Types;

public class StructParser
{
    private int _index;
    private readonly string _text;

    private StructParser(string text)
    {
        _text = text;
        _index = 0;
    }

    public static Dictionary<string, string> Parse(string text)
    {
        return new StructParser(text).Parse();
    }

    private Dictionary<string, string> Parse()
    {
        Dictionary<string, string> result = new();
        Required("(");
        while(_text[_index] != ')')
        {
            var key = ReadSymbol();
            Required("=");
            var quoted = Optional("\"");
            var value = ReadSymbol();
            if (quoted)
                Required("\"");
            SkipSpace();
            result.Add(key, value);
            if(!Optional(","))
                break;
        }
        Required(")");
        return result;
    }

    private string ReadSymbol()
    {
        SkipSpace();
        var result = "";
        while(_index < _text.Length && char.IsLetterOrDigit(_text[_index]))
        {
            result += _text[_index];
            _index++;
        }
        if (result == "")
        {
            throw new Exception("Expected symbol at " + _index);
        }
        SkipSpace();
        return result;
    }

    private void SkipSpace()
    {
        while (_index < _text.Length && char.IsWhiteSpace(_text[_index]))
        {
            _index++;
        }
    }

    private bool Optional(string s)
    {
        if (!_text[_index..].StartsWith(s))
            return false;
        _index += s.Length;
        SkipSpace();
        return true;
    }
    
    private void Required(string s)
    {
        if (!_text[_index..].StartsWith(s))
        {
            throw new Exception("Expected " + s + " at " + _index);
        }
        _index += s.Length;
        SkipSpace();
    }
}