package com.cardmultigame.entities.cards;

public class Card {
    private final String rank;
    private final String colour;

    public Card(String rank, String colour) {
        this.rank = rank;
        this.colour = colour;
    }

    public String rank() { return rank; }
    public String colour() { return colour; }

    @Override
    public String toString() {
        return "r: " + rank + " c: " + colour;
    }
}
