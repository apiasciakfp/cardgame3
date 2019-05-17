using System;
using System.Collections.Generic;
using System.Text;

namespace Core._Extras.Visitor
{

    public class ConfigurableKnife : IVisitor
    {
        private Dictionary<string, string> Mapping { get; set; }
        string _name = "Nóż";

        public ConfigurableKnife(Dictionary<string, string> mapping) => this.Mapping = mapping;

        private string VisitAnything(string name)
        {
            return _name + Mapping[name] + name;
        }

        public string VisitApple(Apple apple) => VisitAnything(apple.Name());
        public string VisitBread(Bread bread) => VisitAnything(bread.Name());
        public string VisitFish(Fish fish) => VisitAnything(fish.Name());
    }
    
}
