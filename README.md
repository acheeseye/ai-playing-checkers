# AI PLAYING CHECKERS
This is a project dedicated to creating and training an AI to play pro level checkers/draughts for UAF CS 405/605.  
# Versions
Version 0:  
- All relevant current files added.
- Board object creates a 12 by 12 board with a boarder with width of 2.
- Board object correctly generates Piece objects according to playable positions.
- Board function print_board displays Board object for debugging purposes.
- Piece objects display correct \*true positions and directions (\*numerical position starting at top left and incrementing right).
- Piece objects may become king, however no movements currently allow it.
- main.cpp draws the Board object and displays existing Piece values.
Version 1:
- All files updated.
- Board function move_piece allows movement for player 1 (starting player).
- TODO: Remove Board function is_empty
- New Board functions init_board, clear_board, is_boarder, and updated_board used to update Board object correctly for print_board.
- Board construction now only initializes values.
- TODO: Use initializer list for constructor.
- Various new data members for Board objects to keep track of Piece object owners and turn order.
- New Board function pass_turn and turn checking in move_piece not working properly.
# Non-Version Related Comments
- (JH) Currently working on collision check/move piece functions. Feel free to make your own and/or put together a GUI!
