package com.cardmultigame;

import com.cardmultigame.iface.UiLogicDispatcher;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        UiLogicDispatcher dispatcher = new UiLogicDispatcher();
        StringBuilder builder = new StringBuilder();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("Please, input the command with proper separators\n");

            String orders = scanner.nextLine();
            builder.append(orders.trim());

            if (orders.contains("SETUP")) {
                String actualOrders = builder.toString();
                builder = new StringBuilder();
                dispatcher.setupGame(actualOrders);
            } else if (orders.contains("EXIT")) {
                break;
            } else {
                dispatcher.doStuff(orders);
            }

            System.out.println(dispatcher.displayCurrentState() + System.lineSeparator());
        }

        scanner.close();
    }
}
