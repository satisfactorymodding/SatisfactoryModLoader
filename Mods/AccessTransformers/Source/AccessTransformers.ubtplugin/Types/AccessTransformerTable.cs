using System;
using System.Collections.Generic;
using System.Linq;

namespace AccessTransformers.Types;

public class AccessTransformerTable<TAccessTransformerType> where TAccessTransformerType : AccessTransformers.BaseAccessTransformer
{
    private readonly Dictionary<string, List<TAccessTransformerType>> _pluginTransformers = new();
    private readonly List<TAccessTransformerType> _usedTransformers = new();
    
    public void Add(string pluginName, TAccessTransformerType transformer)
    {
        if (!_pluginTransformers.ContainsKey(pluginName))
            _pluginTransformers.Add(pluginName, new List<TAccessTransformerType>());
        _pluginTransformers[pluginName].Add(transformer);
    }

    public List<TAccessTransformerType> GetFor(string className, string? alternativeClassName)
    {
        List<TAccessTransformerType> result = new();
        foreach (var (_, transformers) in _pluginTransformers)
        {
            result.AddRange(transformers.Where(transformer => transformer.Class == className || transformer.Class == alternativeClassName));
        }

        return result;
    }
    
    public void MarkUsed(TAccessTransformerType transformer)
    {
        _usedTransformers.Add(transformer);
    }
    
    public List<Tuple<TAccessTransformerType, string>> GetUnusedTransformers()
    {
        List<Tuple<TAccessTransformerType, string>> unusedTransformers = new();
        foreach (var (pluginName, transformers) in _pluginTransformers)
        {
            unusedTransformers.AddRange(from transformer in transformers
                where !_usedTransformers.Contains(transformer)
                select new Tuple<TAccessTransformerType, string>(transformer, pluginName));
        }

        return unusedTransformers;
    }
}