using System;
using System.Collections.Generic;
using System.Text;

namespace Core._Extras.Visitor
{
    public interface IFood
    {
        string Accept(IVisitor visitor);
    }

    public class Fish
    {
        public string Name() => "Rybę";

        public string Accept(IVisitor visitor) =>
            visitor.VisitFish(this);
    }

    public class Apple
    {
        public string Name() => "Jabłko";

        public string Accept(IVisitor visitor) =>
            visitor.VisitApple(this);
    }

    public class Bread
    {
        public string Name() => "Chleb";

        public string Accept(IVisitor visitor) =>
            visitor.VisitBread(this);
    }

}
