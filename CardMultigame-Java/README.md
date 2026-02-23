# Card Multigame — Java

A card guessing game where you try to match a randomly drawn card from the deck.

## How to Run

```bash
mvn compile exec:java
```

## REPL Commands

The game is a text-based REPL. You type commands, the game displays updated state.

### Step 1: Setup

Type a setup string ending with `SETUP`:

```text
Play GuessACard; SetDeck JH,QH,KH,AH,10H; SetMaxTurns 5; SETUP
```

### Step 2: Play

Type guess commands (must end with separator):

```text
Guess QH;
```

### Step 3: Exit

```text
EXIT
```

## Setup Commands

| Command | Example | Effect |
|---------|---------|--------|
| `Play` | `Play GuessACard` | Selects game type (currently only GuessACard) |
| `SetDeck` | `SetDeck JH,QH,KH` | Custom deck (rank + suit: 2-10, J, Q, K, A + S, H, D, C) |
| `SetMaxTurns` | `SetMaxTurns 5` | Maximum number of guesses before defeat |
| `GameVariant` | `GameVariant RedBlack` | Changes comparison to red/black colour only (H,D=red; S,C=black) |

If `SetDeck` is omitted, the default deck is 9-to-A in all 4 suits (24 cards).
If `SetMaxTurns` is omitted, the default is 5 turns.

## Gameplay Commands

| Command | Example | Effect |
|---------|---------|--------|
| `Guess` | `Guess QH` | Guess a card. A random card is drawn from the deck and compared to your guess. |

## How Guessing Works

When you type `Guess QH`:

1. A **random card is drawn** from the deck (and removed)
2. Your guess is compared to the **drawn card** (not the whole deck)
3. **Strict mode** (default): exact rank AND suit must match
4. **RedBlack mode**: only colour family must match (Hearts/Diamonds = red, Spades/Clubs = black)
5. If match: **Victory**. If no match and turns exhausted: **Defeat**.

This means guessing a card that IS in the deck can still miss — it depends on which card the random draw picks.

## Separator Rules

Commands are separated by ONE type of separator. The parser picks whichever separator appears first in the string:

| Separator | Command separator | Card list separator |
|-----------|-------------------|---------------------|
| Mode 1 | `;` semicolons | `,` commas |
| Mode 2 | `,` commas | `;` semicolons |
| Mode 3 | `-` dashes | `,` or `;` |

**Important**: Every command (including the last) must be followed by a separator. `Guess QH;` works. `Guess QH` alone crashes.

## Tests

```bash
mvn test
```

`TestEndToEnd.fullScenario_setup_miss_hit_victory_thenGameIgnoresCommands` walks through a complete game step by step with assertions after every command: setup (3-card deck, 3 max turns) → Turn 1 miss (guessed 2C, drew JH) → Turn 2 hit (guessed QH, drew QH → Victory) → Turn 3 ignored (game already finished). Uses `AlwaysFirstSelector` for deterministic draws.

## Example Session

```text
Please, input the command with proper separators

Play GuessACard; SetDeck JH,QH,KH,AH,10H; SetMaxTurns 5; SETUP
MaximumTurns=5;
CardDeck=Deck: ||r: J c: H||r: Q c: H||r: K c: H||r: A c: H||r: 10 c: H;
IsGameFinishedWithVictory=false;
IsGameFinishedWithDefeat=false;
CurrentTurnNumber=0

Please, input the command with proper separators

Guess 2C;
MaximumTurns=5;
Guess=false;
CardDeck=Deck: ||r: Q c: H||r: K c: H||r: A c: H||r: 10 c: H;
IsGameFinishedWithVictory=false;
IsGameFinishedWithDefeat=false;
CurrentTurnNumber=1

Please, input the command with proper separators

Guess QH;
MaximumTurns=5;
Guess=true;
CardDeck=Deck: ||r: K c: H||r: A c: H||r: 10 c: H;
IsGameFinishedWithVictory=true;
IsGameFinishedWithDefeat=false;
CurrentTurnNumber=2

Please, input the command with proper separators

EXIT
```
