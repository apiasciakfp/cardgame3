using Core._Extras.Visitor;
using NUnit.Framework;
using System;
using System.Collections.Generic;
using System.Text;

namespace CoreTests
{
    public class TestVisitor
    {
        [Test]
        public void SeeCombinations()
        {
            Apple apple = new Apple();
            Fish fish = new Fish();
            Bread bread = new Bread();

            IVisitor tool;

            tool = new Knife();

            Assert.IsTrue("Nóż odgnieżdża Jabłko" == apple.Accept(tool));
            Assert.IsTrue("Nóż kroi Chleb" == bread.Accept(tool));
            Assert.IsTrue("Nóż patroszy Rybę" == fish.Accept(tool));

            tool = new Peeler();

            Assert.IsTrue("Obieraczka obiera Jabłko" == apple.Accept(tool));
            Assert.IsTrue("Obieraczka odskórkowuje Chleb" == bread.Accept(tool));
            Assert.IsTrue("Obieraczka odłuskowuje Rybę" == fish.Accept(tool));

            tool = new MicrowaveOwen();

            Assert.IsTrue("Mikrofalówka gotuje Jabłko" == apple.Accept(tool));
            Assert.IsTrue("Mikrofalówka odnawia Chleb" == bread.Accept(tool));
            Assert.IsTrue("Mikrofalówka podgrzewa Rybę" == fish.Accept(tool));


        }

        [Test]
        public void SeeCombinationsWithMapping()
        {
            Apple apple = new Apple();
            Fish fish = new Fish();
            Bread bread = new Bread();

            IVisitor tool;

            Dictionary<string, string> mapping = new Dictionary<string, string>
            {
                { "Jabłko", " odgnieżdża " },
                { "Chleb", " kroi " },
                { "Rybę", " patroszy " }
            };

            tool = new ConfigurableKnife(mapping);

            Assert.IsTrue("Nóż odgnieżdża Jabłko" == apple.Accept(tool));
            Assert.IsTrue("Nóż kroi Chleb" == bread.Accept(tool));
            Assert.IsTrue("Nóż patroszy Rybę" == fish.Accept(tool));

            mapping["Jabłko"] = " tnie ";

            Assert.IsTrue("Nóż tnie Jabłko" == apple.Accept(tool));
        }
    }
}
