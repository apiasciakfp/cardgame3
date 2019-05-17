using System;
using System.Collections.Generic;
using System.Text;

namespace Core._Extras.Visitor
{
    public interface IVisitor
    {
        string VisitFish(Fish fish);
        string VisitApple(Apple apple);
        string VisitBread(Bread bread);
    }

    public class Knife : IVisitor
    {
        string _name = "Nóż";

        public string VisitApple(Apple apple)
        {
            return _name + " odgnieżdża " + apple.Name();
        }

        public string VisitBread(Bread bread)
        {
            return _name + " kroi " + bread.Name();
        }

        public string VisitFish(Fish fish)
        {
            return _name + " patroszy " + fish.Name();
        }
    }

    public class Peeler : IVisitor
    {
        string _name = "Obieraczka";

        public string VisitApple(Apple apple)
        {
            return _name + " obiera " + apple.Name();
        }

        public string VisitBread(Bread bread)
        {
            return _name + " odskórkowuje " + bread.Name();
        }

        public string VisitFish(Fish fish)
        {
            return _name + " odłuskowuje " + fish.Name();
        }
    }

    public class MicrowaveOwen : IVisitor
    {
        string _name = "Mikrofalówka";

        public string VisitApple(Apple apple)
        {
            return _name + " gotuje " + apple.Name();
        }

        public string VisitBread(Bread bread)
        {
            return _name + " odnawia " + bread.Name();
        }

        public string VisitFish(Fish fish)
        {
            return _name + " podgrzewa " + fish.Name();
        }
    }

}
