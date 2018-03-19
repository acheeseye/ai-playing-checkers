# AI PLAYING CHECKERS

This is a project dedicated to creating and training an AI to play pro level checkers/draughts for UAF CS 405/605.

# Deliverables

PROJ2

- [x] Create a neural network with random weights. (2/18, JH)
- [x] Solve the neural network. (2/18, JH)
- [x] Add a minimax search with a piece count evaluation function. (2/XX, JK)

PROJ3

- [x] Modify random neural network to specified uniformly distributed range. (2/18, JH)
- [x] Given neural network, create offspring. (2/18, JH)
- [x] Test program to check correctly generated gaussian pseudo-random values (non NN-related).
- [ ] Test program to check offsprings lie on the gaussian curve.

PROJ4

- [ ] Implement alpha-beta pruning.
- [x] Generation manager (`OffspringProducer`).
- [x] Determine file storage structure.
- [ ] Testing (hand examine games played & test children in gaussian curve).

# Task List

- [x] Apply board evaluation function to mini-max/alpha-beta.
- [x] Feed piece count into final board eval (can this be done with just two connectors?).
- [ ] Testing for `NeuralNetwork_PERF`.
- [ ] Modify draw condition.
- [ ] Calculate and record branch factor.
- [ ] Remove original `NeuralNetwork`.
- [ ] Implement alpha-beta pruning.

# Useful Resources

- [Here](https://www.youtube.com/watch?v=bhrC84zp9X8) is the YouTube video that worked for me on getting SFML to work.
- [Here](https://msdn.microsoft.com/en-us/library/chh3fb0k.aspx) is documentation for pragma optimize to get more accurate timing.

# IMPORTANT

- I've commented out gnuplot related files because I could not figure out how to get them to work. (JH)
- With my attempts to use g++ to compile this project, it seemed to have issues with `std::exceptions`. Instead, the system now does a console print out and may or may not return after.

# Versions

## Version 6

### Version 6.5

- `main_state` `NERUAL_NETWORK_OFFSPRING` renamed to `GEN0_GENERATE` (call this to produce 30 random networks for GEN0).
- Modified `REPLAY_SAVED_GAME` to allow for replaying drawed games.
- New setting for `NNvNN` `gens_to_train`.
- Timing done for each generation and stored in `timing.txt` in `nn_topologies`.
- New function `NeuralNetwork_PERF::set_player` to hopeufully fix the issue of both networks playing for the same side.

### Version 6.4

- With version 6.3, some network plays were very questionable and seemed like it did not consider piece count what-so-ever.
- [x] TODO: I will provide all games of NN20 (best performing) of GEN9 for replay purposes.
  - This is located in `previous_gen_folder` folder.
- Voiding `MAIN_STATE::PLAY_CHECKERS` because of interactivity with modified `min_max_search`.
- `min_max_search` now takes `NeuralNetwork_PERF` as an additional parameter and calculates each "leaf board" (at the end of the ply).
- Increase modularity for `NeuralNetwork_PERF` to allow mutation to same object during runtime.
- New function `NeuralNetwork_PERF::get_result` returns result (for `min_max_search` to eat).
- New function `temp_Board::get_board_as_vector` returns `m_board`.
- New training method (ply = 2) takes ~35 minutes to train 10 generations.

### Version 6.3

- [x] TODO: Create `results.txt` per `NNvNN` generation.
  - Per line, the active network ID is followed by 5 networks played, then followed by results of the game, respectively (space delimited).
- [x] TODO: Draws denoted.
- [ ] TODO: Change number of moves to draw to 40?
- Storage structure:
  - `GEN#GENID#` directory contains:
    - all 30 network topologies
    - `games_played_#GENID#` directory for games played
      - games played
      - 150 games result file (`result.txt`) (this will allow easier determination for which networks survived)
  - example access to generation 5 game results: `fin.open("ai-playing-checkers//nn_topologies//GEN5//games_played_5//result.txt", ifstream::in);`
- [ ] QUES: Should the set of 5 games played by each network switch who starts first?
- [ ] QUES: Record lineage?
- [x] TODO: CHANGE PLY TO (at least) 4.
- [x] TODO: Use `NerualNetwork_PERF::calculate` for `mini_max_search` return values.
- Fixed `OffspringProducer` issues with vector indicies.
- More comments in `OffspringProducer.cpp`.
- `NNvNN` now trains through 10 generations with 1 ply mini max (CURRENTLY NO BOARD EVALUATIONS!!!).
  - INSTRUCTIONS TO RECREATE:
    1. Delete all GENX directories (leave naming_status.txt).
    2. Run `NEURAL_NETWORK_OFFSPRING` to produce 0th generation randomly generated networks.
    3. Run `NNvNN` and set desired generations (default to 10, at the moment) to train.
        - 10 generations with 1 ply is about 5~10 minutes, roughly.
  - Produces offspring for the 10th generation but does not play itself on 10th generation.
  - Interestingly, 1 ply mini max values kings as at least 2.0.
- New `OffspringProducer` functions:
  - `determine_survivors`: sets `m_survived_parents` to all topologies that placed top 15 (in string form).
  - `produce_next_generation`: records survivors from previous generation and calls `produce_offspring` on it. Offspring topologies come right after parent topologies after GEN0.
    - [ ] TODO: Perhaps collapse `determine_survivors` into this function.
  - `get_current_generation_id`: returns generation ID according to naming_status.txt.

### Version 6.2

- New `main_state` `NNvNN` which handles network vs network play.
- `main_state`s `NEURAL_NETWORK_TESTING` and `NEURAL_NETWORK_TIMING` removed due to irrelevance.
- [x] TODO: new generations need to generate new folder within directory to hold games played.
  - (this is hard coded for GEN0)
- Heuristics of network vs network:
  - Active network is always red.
  - Opposing network plays first move.
  - 3 randomly generated moves will be made at the beginning.
  - Networks will not play itself or a repeated network.
  - Reaching move 100 indicates a draw.
  - Networks use 4-ply for minimax iteration.
  - 5 games per network with population of 30 networks: 150 games played.
  - Games played stored in `games_played_#GENID#` folder found in respective generation directory where `#GENID#` is replaced with the generation it is in.
    - Gameplay results will also be stored in that folder under `results.txt`.
    - Games played will be named `#ACTIVE#_#OPPO#.txt`.

### Version 6.1

- Completed saved games can now be replayed using the `REPLAY_SAVED_GAME` option for the `main_state`.
- The controls for this option are as follows:
  - `Spacebar`: toggles automatic/manual stepping modes; manual stepping is the default stepping mode. When in automatic stepping mode, manual stepping mode can also be engaged by pressing either the left or right arrow key.
  - `Right Arrow Key`: steps forward in manual stepping mode.
  - `Left Arrow Key`: steps backward in manual stepping mode.
  - The `R` key: restarts the board when end of game has been reached in automatic stepping mode.
  - The `Q` key: to quit.

### Version 6.0

- New class `OffspringProducer` added. This class
  - generates random parent topology.
  - records parent topology to specified directory.
    - This currently only supports a single generation and a population of 30.
    - King value and weights are delimited by `9999` while weights and sigma variables are delimited by `8888`.
    - `ofstream::trunc` is used as an argument so previous topology text files will be overwritten per `main` run.
  - read and writes to `nn_topologies\naming_status.txt` to perform network naming.
  - does not produce offspring yet.
- New `main_state` `NEURAL_NETWORK_OFFSPRING`.
- Class `NeuralNetwork_PERF` topology generation moved to `OffspringProducer` for reasons:
  - Declutter `NeuralNetwork_PERF`.
  - Array \[] operations were somehow getting overwritten when transferring from `NeuralNetwork_PERF` to `OffspringProducer`.
- `topo_proof_x.txt` files added as readable verification that the current version of topology generator works correctly.
- Added separate Gaussian number generator with graphs. This can be found in `gnugraph` along with further documentation for the generator.
  - The main for the Gaussian number generator has been merged into `main.cpp`.

## Version 5

### Version 5.5

- New class `NeuralNetwork_PERF` added.
- New class provides about estimated 130% performance of `NeuralNetwork`.
- For some reason, `NeuralNetwork` timing became about 30% slower with recent runs (crowded `main.cpp`? new testing calculation functions added to `NeuralNetwork`? just machine things?).
- On my(JH) machine, it is currently consistent around 95,000 BEF/sec with the sigmoid function (slightly worse than `NeuralNetwork`, but better now with `NeuralNetwork` slowing down).
- New `main_state` `NEURAL_NETWORK_TIMING_PERF` for timing `NeuralNetwork_PERF`.
- No current test cases for `NeuralNetwork_PERF`.
- [ ] ~~TODO: Move `GLOBAL_SIGMA_VALUE` to `NeuralNetwork_PERF` and remove `GLOBAL_WEIGHT_COUNT` from `NeuralNetwork` as it is calculated in `NeuralNetwork_PERF`~~ No longer relevant due to new topology generation. 
- [ ] TODO: Perhaps remove `NeuralNetwork` to unclutter the project solution (and perhaps helps with increasing the BEF speed?).

### Version 5.4

- `NeuralNetwork` now uses arrays for calculations instead. Uses hard coded values for sizes.
  - Both `std::vector` and `std::array` compute at least 10 (100? forgot the numbers) times slower than using arrays, thus array computation have been chosen.
    - I can provide the code for the tests if needed.
  - Due to the nature of arrays, their size is statically allocated thus hard-coded global values are used for initialization.
  - Hard-coded values apply to Blonde24 and simple test-case of 4-3-2-1 topology.
- `NeuralNetwork` BEF/sec is now roughly 150,000 **WITHOUT** applying sigmoid.
- [x] TODO: apply sigmoid.
- `NeuralNetwork` BEF/sec is around 100,000 with sigmoid on my machine.
- [ ] TODO: further optimize to get to around 500,000 BEF/sec?
- `Main.cpp` now has new states for `PLAY_CHECKERS`, `NEURAL_NETWORK_TESTING`, and `NEURAL_NETWORK_TIMING` for ease of switching between `main_modes` (thus `NeuralNetwork_main.cpp` is now merged with `main.cpp`).
- Testing mode implemented in `NEURAL_NETWORK_TESTING`.

### Version 5.3

- Classes `Connector` and `NNNodes` removed for simplicity.
- Class `NeuralNetwork` now computes the "board evaluation" (Now called `calculate_output`).
- Class `NeuralNetwork` now require more modular initialization.
- [x] TODO: Perhaps create a thin wrapper for default initialization ~~(or a multi-parametered function)~~.
- [x] TODO: Fix an issue where `init_weights_and_sigmoid` needs `set_player` to be called first.
- [x] TODO: Test calculated output to be random?
- [x] TODO: Write `NeuralNetwork` king value, weights, and sigma to a file.
- Class `NeuralNetwork` now applies sigmoid function (forgot about this in the previous commit).
- Fixed an issue where `NeuralNetwork` would initialize new weights per board evaluation instead of using the previous ones.
- [ ] ~~TODO: Might need testing for above to be sure~~. No longer relevant.
- Timing done in `NeuralNetwork_main.cpp` for average BEF/sec and BEF/15 sec: averaging around 700~900 BEF per second (that's OK??)
- `NeuralNetwork_main.cpp` now also tests the timing for a six layer >10,000 weights `NeuralNetwork` and prints the related calculations (requirements 1 & 2 fulfilled for PROJ2 deliverables).
- `NeuralNetwork` now writes its topology values to file `brunette26_topology_gen0.txt` within the `nn_topologies` with first line as the `m_king_value` and the subsequent lines as a pair of weight and its corresponding sigma value.
  - User must use `NeuralNetwork::set_generate_file(true)` to write the topology, as it is set to false on default.
  - [x] TODO: Figure out how to name the different topologies (same as convention for games played? yes, can do that).
  - Topologies now have unique names in the same style as recorded games. Note that this name does _not_ correlate the recorded game file to the topology file generated for it (would it be preferable to give topologies the same date/time as the recorded game that they are generated for?).
- [x] TODO: Live piece count displayed.
- AI player now prioritizes piece count when deciding its next move.

### Version 5.2

- New class `Connector` with randomized weights.
- Each `NNNodes` in the `NeuralNetwork` has the correct amount of `Connectors` to the next layer.
- `Connectors` generate randomized values correctly.
- Working on reading game data for function `NeuralNetwork::board_evaluation`.
- [ ] ~~Somehow parse the ugly bullshit I've created as compressed game data OR~~
- [x] Write new function to store game data with 32 numbers per game move and read that file instead.
- `process_output` rewritten to do that, code has been added to `board_evaluation` to read in, parse, and store the data.
- [x] TODO: Iterate through files in directory? (so that names don't have to be hard-coded)
- [ ] ~~TODO: Instead of defaulting `Connectors` to next layer only, allow user to pass in `layer_id` for diversified connection~~. Class `Connectors` no longer exists.

### Version 5.1

- New `temp_Board` function `write_board_to_file` that takes a file name and write the board status of all 32 positions for every single move made in a compressed binary style.

||Playable|Red Soldier|Red King|Black Soldier|Black King|
|---|---|---|---|---|---|
|Binary|`100`|`010`|`011`|`000`|`001`|
|Hex|`0x4`|`0x2`|`0x3`|`0x0`|`0x1`|

- The data is stored by rows and each row is denoted by a unsigned short (16-bit) and the first 4 bits are not used. For example, the decimal value `1170` is `0000010010010010` in binary, and is broken up into `0000` `010` `010` `010` `010` where the 3-bit sections represent the piece type (in the table above).
- I am unsure if storing them as binary/hex will cost less memory, please alter accordingly if you please.
- Integers are stored memory in binary format already.
- `NNNodes` objects now use a new sigmoid function for processing inputs. This allows for the range of inputs/output to be in the range of -1 and 1.
- [x] TODO: Create class `connectors` that take an input and apply a weight and bias to it accordingly.
- [x] TODO: Contemplate if `connectors` need to be a class or if this should be internally handled by the `NNNodes` objects.
- [x] TODO: Do some timing optimizations (simplified sigmoid calculation?).
  - [This](http://www.meta-calculator.com/?panel-102-graph&data-bounds-xMin=-8&data-bounds-xMax=8&data-bounds-yMin=-11&data-bounds-yMax=11&data-equations-0=%22y%3D1%2F(1%20%2B%20e%5E(-x))%22&data-equations-1=%22y%3D(0.5*(x%2F1%2Bx))%2B0.5%22&data-rand=undefined&data-hideGrid=false) graph page (click add equations and add the two the plot it I think) shows the difference between the sigmoid function and the "faster and approximated" function mentioned [here](https://stackoverflow.com/questions/10732027/fast-sigmoid-algorithm) by Nosyara. I don't believe it will be a useful approximation.

### Version 5.0

- New classes `NeuralNetwork` and `NNNodes` for creating AI.
- New classes are currently useless.

## Version 4

### Version 4.4

- Right arrow key now generates a random move for whosever turn it is.
- Resource files (`*.png` and `*.ttf` files) are now stored in the `res` directory.
- [x] TODO: Make a directory to store the gameplay files/change the storing directory for the `std::ofstream`.
- [ ] ~~Or keep track of them ourselves?~~
- [ ] ~~Do we need to make sure no overlapping names when trying to congregate our games played?~~

### Version 4.3

- Identified issue causing crash where both players are to be random AI and only one piece is remaining on either side, it was because of attempted division by 0 when randomizing. Issue is now resolved.
- Added images and replaced `CircleShape piece` with `Sprite piece`.
- Window does not auto-close at end of game and notes who the winner is.
- [x] TODO: Visually execute the winning move before `board.is_over()` evaluates to `true`.
- [x] TODO: Examine rules to determine what should happen when a given player is unable to make any moves (currently the player who is not unable to make moves auto-wins). This happens when a player has one piece left, that piece is in a corner or up against the wall, and it is the other player's turn to move.
- "The player who cannot move, because he has no pieces, or because all of his pieces are blocked, loses the game." http://www.chesslab.com/rules/CheckerComments.html

### Version 4.2

- `temp_Board` objects now allow either player to go first.
- Allows (ish) for both players to be random AI (when `black_is_ai` and `red_is_ai` are both set to true and there is only one piece remaining from either side, the game crashes).
- Above seems to be resolved (?). Just did a game that ended with 0 black pieces.
- Added a delay between each move for viewing.
- [x] TODO: Save the moves made and win status and output it to a (text?) file.
- When the program is run, a game file (`.txt`) is created; the generated file name contains the current date and time. The file contents are space-delimited and each line contains `r` or `b` followed by the move it took, except for the last line which is either `R` or `B` depending on who won the game.

### Version 4.1

- Pieces are now displayed smaller allowing the top left corner of the playable slot to display slot id (for easier debugging and/or readability).
- [x] TODO: Change the white board base because it hurts my eyes a little.
- Now sports a classy dark brown board base.

### Version 4.0

- New class `temp_Board` is used to keep track of board status and pieces.
- [x] TODO: Delete `piece.cpp` and `piece.h` files.
- King moves and jumps correctly for single pieces.
- In order to perform a multi-jump, the user must override mouse-click mode by pressing the `M` key and choose a move ID.
- Move IDs can be generated by pressing the `F` key.
- Simple GUI implemented (with selection indication included).
- Right side of GUI to be implemented as move display, or something to the likes.
- [x] TODO: Check if kings are properly produced when a multi-jump is attempted and the slot the piece lands on is **NOT** a king transformer slot.\*\*\*
- [ ] ~~TODO: Perhaps clean-up `main.cpp` by creating GUI drawer objects?~~ `main.cpp` is very messy now with other stuff.
- `_RED_` player is by default and AI with random moves generated and `_BLACK_` is user.
- [x] TODO: Test if reverse works and if both can be AI.

## Version 3

### Version 3.2

- Soft save so progress is not lost.
- Kings are now able to jump in opposite direction.
- Kings are not displayed correctly when they move from king spot.
- 3.2.1 hot fix(?) Kings are now displayed correctly at all times.

### Version 3.1

- Kings now update and print correctly when they reach the king spots.
- King are not able to jump in the opposite direction (can move in opposite direction).
- Soft save so progress is not lost.

### Version 3.0

- [x] TODO: Multijumping to be implemented.
- [x] TODO: King transformation movement (becomes king, but crashes right after).
- [ ] ~~TODO: Allow console to generate moves correctly when using 0 0.~~
- Player 1 and 2 are now renamed to Player BLACK and RED, respectively.
- Black pieces are now at the bottom (as required for assignment).
- Various new data members and functions to store and retrieve moves made, moves possible, and jumps possible.
- `valid_man_move` is renamed to `generate_valid_moves` with different functionality. The function now generates all possible moves and stores in `m_all_possible_xxxxx_for_current_player`.
- Fixed an issue where `m_alive == dead` Piece objects were still left on the board and considered in play.
- Beginning stages of king transformation attempted to be implemented.
- `main.cpp` now allows for more interactive debugging with taking console input.
- `move_piece` function now takes the location of a piece as its first parameter (as opposed to `piece_id`). Invalid locations allow player to retry a different location.

## Version 2

- All files updated.
- `move_piece` allows both players to move to empty spaces and jump correctly.
- New Board function `ownership_check` to make sure opposing player cannot move each other's pieces.
- New Board function `valid_man_move` to check if move declared by `move_piece` is a valid move, and initiates jump events if needed (for man/men/non-king units only).
- New Board function `get_piece_id` retrieves the ID of a Piece object located on a certain position on the board (kind of sketchy, but it seems to work ok and I don't know how else to retreive the piece's index).
- Piece objects now keep track of their livelihood through `m_alive`.

## Version 1

- All files updated.
- Board function `move_piece` allows movement for player 1 (starting player).
- [ ] ~~TODO: Remove Board function `is_empty`.~~ This proved to be useful.
- New Board functions `init_board`, `clear_board`, `is_boarder`, and `update_board` used to update Board object correctly for `print_board`.
- Board construction now only initializes values.
- [x] TODO: Use initializer list for constructor.
- Various new data members for Board objects to keep track of Piece object owners and turn order.
- New Board function `pass_turn` and turn checking in `move_piece` not working properly (fixed: issue #1).

## Version 0

- All relevant current files added.
- Board object creates a 12 by 12 board with a boarder with width of 2.
- Board object correctly generates Piece objects according to playable positions.
- Board function `print_board` displays Board object for debugging purposes.
- Piece objects display correct \*true positions and directions (\*numerical position starting at top left and incrementing right).
- Piece objects may become king, however no movements currently allow it.
- `main.cpp` draws the Board object and displays existing Piece values.

# Non-Version Related Comments

- [x] Currently working on collision check/move piece functions. Feel free to make your own and/or put together a GUI! (1/24, JH)
- [ ] ~~Currently working on implementing king transformations/movements.~~ (1/25, JH)
- [x] Currently working on all possible move generation. (1/25, JH)
- [x] Currently working on implementing king movements and debugging transformation. (1/26, JH)
- [ ] ~~Currently working on implementing multijumping.~~ (1/29, JH)
- [x] Currently working on implementing mouse click based GUI. (1/31, JH)
- [ ] ~~Currently contemplating if SFML related objects should be handled within a class.~~ No for now. (2/1, JH)
- [ ] ~~Devising a way to playback and store game info.~~ Game info storing done by someone else. (2/6, JH)
- [x] Random move generated by using right arrow. (2/13, JH)
- [ ] ~~Left arrow should move backwards?~~ I'm ok on that. (2/13, JH)
- [x] Figuring out how to implement the neural network. (2/14, JH)
- [x] `NeuralNetwork` should iterate through all boards (currently only one). (2/17, JH)
- [x] Further optimize speed for `calculate_output`? (2/18, JH)
- [ ] Even more optimizie for calculate_output. (2/23, JH)
  - (below are timing results of `NeuralNetwork_PERF`)
  - 90,000 BEF/sec => compiled with Visual Studio on a Surface Pro 3 with -O2 turned on
  - 120,000 BEF/sec => compiled with g++ on the desktop in the computer lab without -O2 turned on
  - 290,000 BEF/sec => compiled with g++ on the desktop in the computer lab with -O2 turned on
- [x] Asexually reproducing `brunette26`. (2/18, JH)
- [ ] Working on implementing `NeuralNetwork_PERF`'s `calculate` function to `mini_max_search`. (3/15, JH)
- Here's a potentially helpful chart for all the playable positions:

|P|L|A|Y|A|B|L|E|
|---|---|---|---|---|---|---|---|
|x|0|x|1|x|2|x|3|
|4|x|5|x|6|x|7|x|
|x|8|x|9|x|10|x|11|
|12|x|13|x|14|x|15|x|
|x|16|x|17|x|18|x|19|
|20|x|21|x|22|x|23|x|
|x|24|x|25|x|26|x|27|
|28|x|29|x|30|x|31|x|
