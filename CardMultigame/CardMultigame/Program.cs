using Core.Interface;
using System;
using System.Text;

namespace CardMultigame
{
    class Program
    {
        static void Main(string[] args)
        {
            var dispatcher = new UiLogicDispatcher();
            var builder = new StringBuilder();

            while(true)
            {
                Console.WriteLine("Please, input the command with proper separators\n");

                string orders = Console.ReadLine();
                builder.Append(orders.Trim());

                if(orders.Contains("SETUP"))
                {
                    var actualOrders = builder.ToString();
                    builder = new StringBuilder();
                    dispatcher.SetupGame(actualOrders);
                }
                else if(orders.Contains("EXIT"))
                {
                    break;
                }
                else
                {
                    dispatcher.DoStuff(orders);
                }
                
                Console.Write(dispatcher.DisplayCurrentState() + System.Environment.NewLine + System.Environment.NewLine);
            }
        }
    }
}
