# AI PLAYING CHECKERS
This is a project dedicated to creating and training an AI to play pro level checkers/draughts for UAF CS 405/605.  
# IMPORTANT  
- [Here](https://www.youtube.com/watch?v=bhrC84zp9X8) is the YouTube video that worked for me on getting SFML to work.
# Versions
## Version 0:  
- All relevant current files added.
- Board object creates a 12 by 12 board with a boarder with width of 2.
- Board object correctly generates Piece objects according to playable positions.
- Board function `print_board` displays Board object for debugging purposes.
- Piece objects display correct \*true positions and directions (\*numerical position starting at top left and incrementing right).
- Piece objects may become king, however no movements currently allow it.
- `main.cpp` draws the Board object and displays existing Piece values.  

## Version 1:
- All files updated.
- Board function `move_piece` allows movement for player 1 (starting player).
- [ ] ~~TODO: Remove Board function `is_empty`.~~ This proved to be useful.
- New Board functions `init_board`, `clear_board`, `is_boarder`, and `update_board` used to update Board object correctly for `print_board`.
- Board construction now only initializes values.
- [ ] TODO: Use initializer list for constructor.
- Various new data members for Board objects to keep track of Piece object owners and turn order.
- New Board function `pass_turn` and turn checking in `move_piece` not working properly (fixed: issue #1).  

## Version 2:
- All files updated.
- `move_piece` allows both players to move to empty spaces and jump correctly.
- New Board function `ownership_check` to make sure opposing player cannot move each other's pieces.
- New Board function `valid_man_move` to check if move declared by `move_piece` is a valid move, and initiates jump events if needed (for man/men/non-king units only).
- New Board function `get_piece_id` retrieves the ID of a Piece object located on a certain position on the board (kind of sketchy, but it seems to work ok and I don't know how else to retreive the piece's index).
- Piece objects now keep track of their livelihood through `m_alive`.  

## Version 3:
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
### Version 3.1:
- Kings now update and print correctly when they reach the king spots.
- King are not able to jump in the opposite direction (can move in opposite direction).
- Soft save so progress is not lost.
### Version 3.2:
- Soft save so progress is not lost.
- Kings are now able to jump in opposite direction.
- Kings are not displayed correctly when they move from king spot.
- 3.2.1 hot fix(?) Kings are now displayed correctly at all times.
## Version 4:
- New class `temp_Board` is used to keep track of board status and pieces.
- [x] TODO: Delete `piece.cpp` and `piece.h` files.
- King moves and jumps correctly for single pieces.
- In order to perform a multi-jump, the user must override mouse-click mode by pressing the `M` key and choose a move ID.
- Move IDs can be generated by pressing the `F` key.
- Simple GUI implemented (with selection indication included).
- Right side of GUI to be implemented as move display, or something to the likes.
- [ ] TODO: Check if kings are properly produced when a multi-jump is attempted and the slot the piece lands on is **NOT** a king transformer slot.
- [ ] TODO: Perhaps clean-up `main.cpp` by creating GUI drawer objects?
- `_RED_` player is by default and AI with random moves generated and `_BLACK_` is user.
- [ ] TODO: Test if reverse works and if both can be AI.
### Version 4.1:
- Pieces are now displayed smaller allowing the top left corner of the playable slot to display slot id (for easier debugging and/or readability).
- [x] TODO: Change the white board base because it hurts my eyes a little.
- Now sports a classy dark brown board base.
# Non-Version Related Comments
- [x] Currently working on collision check/move piece functions. Feel free to make your own and/or put together a GUI! (1/24, JH)
- [ ] ~~Currently working on implementing king transformations/movements.~~ (1/25, JH)
- [x] Currently working on all possible move generation. (1/25, JH)  
- [x] Currently working on implementing king movements and debugging transformation. (1/26, JH)
- [ ] ~~Currently working on implementing multijumping.~~ (1/29, JH)
- [x] Currently working on implementing mouse click based GUI. (1/31, JH)
- [ ] Currently contemplating if SFML related objects should be handled within a class. (2/1, JH)
- Here's a maybe **NOT** helpful chart for all the playable positions (new class uses a different board):  

|P|L|A|Y|A|B|L|E|
|---|---|---|---|---|---|---|---|  
|x|27|x|29|x|31|x|33|  
|38|x|40|x|42|x|44|x|  
|x|51|x|53|x|55|x|57|  
|62|x|64|x|66|x|68|x|  
|x|75|x|77|x|79|x|81|  
|86|x|88|x|90|x|92|x|  
|x|99|x|101|x|103|x|105|  
|110|x|112|x|114|x|116|x|
