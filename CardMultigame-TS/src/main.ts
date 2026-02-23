import * as readline from "node:readline";
import { UiLogicDispatcher } from "./iface/UiLogicDispatcher.js";

const dispatcher = new UiLogicDispatcher();
let builder = "";

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

function prompt(): void {
  rl.question(
    "Please, input the command with proper separators\n",
    (orders: string) => {
      builder += orders.trim();

      if (orders.includes("SETUP")) {
        const actualOrders = builder;
        builder = "";
        dispatcher.setupGame(actualOrders);
      } else if (orders.includes("EXIT")) {
        rl.close();
        return;
      } else {
        dispatcher.doStuff(orders);
      }

      console.log(dispatcher.displayCurrentState() + "\n");
      prompt();
    }
  );
}

prompt();
