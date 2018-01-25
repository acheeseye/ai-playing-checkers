# AI PLAYING CHECKERS
This is a project dedicated to creating and training an AI to play pro level checkers/draughts for UAF CS 405/605.  
# Versions
Version 0:  
- All relevant current files added.
- Board object creates a 12 by 12 board with a boarder with width of 2.
- Board object correctly generates Piece objects according to playable positions.
- Board function `print_board` displays Board object for debugging purposes.
- Piece objects display correct \*true positions and directions (\*numerical position starting at top left and incrementing right).
- Piece objects may become king, however no movements currently allow it.
- `main.cpp` draws the Board object and displays existing Piece values.  

Version 1:
- All files updated.
- Board function `move_piece` allows movement for player 1 (starting player).
- [x] ~~TODO: Remove Board function is_empty~~ This proved to be useful.
- New Board functions `init_board`, `clear_board`, `is_boarder`, and `updated_board` used to update Board object correctly for `print_board`.
- Board construction now only initializes values.
- [ ] TODO: Use initializer list for constructor.
- Various new data members for Board objects to keep track of Piece object owners and turn order.
- New Board function `pass_turn` and turn checking in `move_piece` not working properly (fixed: issue #1).  

Version 2:
- All files updated.
- `move_piece` allows both players to move to empty spaces and jump correctly.
- New Board function `ownership_check` to make sure opposing player cannot move each other's pieces.
- New Board function `valid_man_move` to check if move declared by `move_piece` is a valid move, and initiates jump events if needed (for man/men/non-king units only).
- New Board function `get_piece_id` retrieves the ID of a Piece object located on a certain position on the board (kind of sketchy, but it seems to work ok and I don't know how else to retreive the piece's index).
- Piece objects now keep track of their livelihood through `m_alive`.
# Non-Version Related Comments
- (JH) Currently working on collision check/move piece functions. Feel free to make your own and/or put together a GUI! 1/24
- (JH) Currently working on implementing king transformations/movements. 1/25
- Here's a maybe helpful chart for all the playable positions:  

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
