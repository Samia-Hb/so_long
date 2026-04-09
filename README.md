<div align="center">

```
                          
                                                So Long               

```

*A small 2D game built in C with MiniLibX — a 1337 School project*

![Language](https://img.shields.io/badge/Language-C-blue?style=flat-square&logo=c)
![School](https://img.shields.io/badge/School-1337-black?style=flat-square)
![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-orange?style=flat-square)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=flat-square)

</div>

---

## 📖 Table of Contents

- [About the Project](#-about-the-project)
- [Features](#-features)
- [Game Preview](#-game-preview)
- [Map Format](#-map-format)
- [Map Validation Rules](#-map-validation-rules)
- [Controls](#-controls)
- [Project Structure](#-project-structure)
- [Dependencies](#-dependencies)
- [Installation & Build](#-installation--build)
- [Usage](#-usage)
- [How It Works](#-how-it-works)
- [Author](#-author)

---

## 🎮 About the Project

**so_long** is a simple 2D top-down game developed in **C** as part of the **42 School** curriculum. The player navigates a tile-based map, collecting all coins before reaching the exit — all while the game tracks and displays the number of moves made.

The game is rendered using **MiniLibX**, a lightweight graphics library developed for 42, on top of the X11 windowing system.

> The goal is straightforward: collect every coin (`C`) and then step on the exit (`E`) to win.

---

## ✨ Features

- 🗺️ **Custom map loading** — load any `.ber` map file at runtime
- ✅ **Thorough map validation** — rectangle shape, closed borders, valid characters, reachable path
- 🔍 **Flood-fill path checking** — ensures all coins and the exit are accessible from the player's starting position
- 🚶 **Smooth player movement** — move up, down, left, and right with WASD keys
- 🎨 **Directional sprites** — the player sprite changes based on movement direction (left / right)
- 🪙 **Coin collection** — collect all coins to unlock the exit
- 🏁 **Win condition** — reaching the exit after collecting all coins exits the game
- 🖥️ **Move counter** — every move is counted and printed to the terminal
- 🧹 **Memory-safe** — all allocated resources are properly freed on exit

---

## 🖼️ Game Preview

```
┌──────────────────────────────────────┐
│ 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 │
│ 1 E · · C · · · · · · · · · · · · 1 │
│ 1 · · · C 1 C 1 · · 1 · · · · · · 1 │
│ 1 C · · C 1 · · 1 · 1 · · · · · · 1 │
│ 1 · · · · · · · · · · · · · · · · 1 │
│ 1 · · · · · · · · · P · · · · · · 1 │
│ 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 │
└──────────────────────────────────────┘
  P = Player   C = Coin   E = Exit   1 = Wall
```

| Symbol | Tile        | Description                              |
|--------|-------------|------------------------------------------|
| `1`    | 🧱 Wall     | Impassable obstacle; forms map borders   |
| `0`    | 🟫 Floor    | Walkable empty tile                      |
| `P`    | 🧍 Player   | Starting position (exactly one required) |
| `C`    | 🪙 Coin     | Collectible — at least one required      |
| `E`    | 🚪 Exit     | Exit tile — unlocked when all coins are collected |

---

## 🗺️ Map Format

Maps are plain-text files with the `.ber` extension. Each character represents one tile on the grid.

**Example map (`maps/map.ber`):**
```
1111111111111111111111111111111111
1E00C00000000000000001000000000001
1000C1C100100000101001000000010101
1C00C10010101010001001000000010101
1000000000001000000000000000000001
100000000000000100P001000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
10000000010010000000C0000000000001
1111111111111111111111111111111111
```

### Valid Map Characters

| Character | Meaning                      |
|-----------|------------------------------|
| `1`       | Wall                         |
| `0`       | Empty / walkable floor       |
| `P`       | Player starting position     |
| `C`       | Collectible (coin)           |
| `E`       | Exit door                    |

---

## ✅ Map Validation Rules

The program performs extensive validation before the game starts. Any violation causes an error message and a clean exit.

| Rule | Description |
|------|-------------|
| **File extension** | The map file must end with `.ber` |
| **Rectangular shape** | All rows must have the same width |
| **Closed borders** | The entire perimeter must consist of walls (`1`) |
| **Valid characters** | Only `0`, `1`, `P`, `C`, `E` are allowed |
| **Exactly one player** | The map must contain exactly one `P` |
| **Exactly one exit** | The map must contain exactly one `E` |
| **At least one coin** | The map must contain at least one `C` |
| **Valid path** | A flood-fill algorithm verifies that all coins and the exit are reachable from `P` |

---

## 🎮 Controls

| Key | Action         |
|-----|----------------|
| `W` | Move **Up**    |
| `S` | Move **Down**  |
| `A` | Move **Left**  |
| `D` | Move **Right** |
| `ESC` | Quit the game |
| ✕ (window close) | Quit the game |

> Every valid key press increments the move counter printed to the terminal.

---

## 📁 Project Structure

```
so_long/
├── assests/                    # Game sprites (XPM format)
│   ├── wall.xpm                # Wall tile sprite
│   ├── road.xpm                # Floor tile sprite
│   ├── exit.xpm                # Exit tile sprite
│   ├── coin_original.xpm       # Coin tile sprite
│   ├── player_original.xpm     # Player default sprite
│   ├── player_right.xpm        # Player moving right sprite
│   ├── player_left.xpm         # Player moving left sprite
│   └── bonus_assests/          # Additional/bonus sprites
├── Include/
│   └── get_next_line/          # get_next_line library
│       ├── get_next_line.c
│       ├── get_next_line_utils.c
│       └── get_next_line.h
├── maps/                       # Sample map files
│   ├── map.ber                 # Large playable map
│   └── map1.ber                # Small test map
├── minilibx-linux/             # MiniLibX graphics library
├── main.c                      # Entry point; map drawing & game loop
├── so_long.c                   # Window init, texture loading, helpers
├── so_long.h                   # Shared header: structs & prototypes
├── check_arguments.c           # Map validation (shape, borders, chars, count)
├── flood_fill.c                # Flood-fill path validation algorithm
├── move_player.c               # Player movement & key event handling
├── so_long_utils.c             # Map parsing utilities (read file → 2D array)
├── clean_functions.c           # Memory cleanup and safe exit helpers
└── Makefile                    # Build system
```

---

## 🔧 Dependencies

| Dependency | Description |
|------------|-------------|
| **MiniLibX** | Bundled in `minilibx-linux/` — no external install needed |
| **X11 / Xext** | Required system libraries for the display server |
| **cc / gcc** | C compiler |
| **make** | Build automation |

Install X11 development libraries on Debian/Ubuntu:

```bash
sudo apt-get install libx11-dev libxext-dev
```

---

## 🚀 Installation & Build

### 1. Clone the repository

```bash
git clone https://github.com/Samia-Hb/so_long.git
cd so_long
```

### 2. Build MiniLibX (if needed)

```bash
cd minilibx-linux && make && cd ..
```

### 3. Build the project

```bash
make
```

### 4. Clean build artifacts

| Command | Effect |
|---------|--------|
| `make clean` | Remove object files (`.o`) |
| `make fclean` | Remove object files **and** the `so_long` binary |
| `make re` | Full rebuild (`fclean` + `all`) |

---

## 🕹️ Usage

```bash
./so_long <path/to/map.ber>
```

**Examples:**

```bash
# Play the bundled large map
./so_long maps/map.ber

# Play the small test map
./so_long maps/map1.ber
```

**Error cases handled gracefully:**

```bash
# Missing argument
./so_long
# → exits with code 1

# Wrong file extension
./so_long maps/map.txt
# → Error: invalid file extension

# Invalid map (not rectangular, bad characters, no path, etc.)
./so_long maps/bad_map.ber
# → Error: descriptive message + clean exit
```

---

## ⚙️ How It Works

### 1. Map Parsing
The map file is read line by line using the custom **get_next_line** implementation. The program first calculates the map dimensions (width × height), then allocates a 2D `char` array and fills it with the map contents, recording the player's starting position and coin count as it goes.

### 2. Map Validation
Five sequential checks are performed:
1. **File extension** — must end in `.ber`
2. **Valid characters** — only `0 1 P C E` allowed
3. **Rectangular form** — every row must have the same length
4. **Closed borders** — all border tiles must be `1`
5. **Parameter count** — exactly one `P`, one `E`, at least one `C`
6. **Flood-fill** — a recursive flood-fill from `P` verifies every coin is reachable and the exit is accessible

### 3. Rendering
MiniLibX is used to open a window sized `map_width × TILE_SIZE` by `map_height × TILE_SIZE`. Each cell is rendered by placing the corresponding XPM image at its pixel coordinate.

### 4. Player Movement
Key events (`W A S D`) are caught via `mlx_key_hook`. Each direction function:
- Clears the player's current tile (replaces with floor)
- Checks the target tile (`wall`, `coin`, `exit`, or `floor`)
- Moves the player if the tile is passable
- Decrements coin count when a coin is collected
- Triggers a win (clean exit) when stepping on `E` with zero coins remaining
- Updates the player sprite (left-facing or right-facing) accordingly

---

## 👤 Author

**Samia Hb** — 42 Network(1337 coding school) student (`shebaz@student.1337.fr`)

- 📅 Project started: May 2024
- 🎓 School: [42 Network/(1337 school)](https://www.42network.org/) 

---

<div align="center">
  <i>Made with ❤️ and a lot of C at 1337</i>
</div>
