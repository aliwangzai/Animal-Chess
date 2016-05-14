5/3/2016

Board里加入了whowillMove, 是指真正要走子的人。curplayer会随AI的思考而变化。评估时，就用whowillmove这个player的分数系统。
另外，Piece里每个分数值都有两个了。一个是Player0的分数系统，另一个是player1的分数系统。

Added whowillMove to Board, which indicates the real player who will move next round. Curplayer is used in the thinking process, so that it will changes when the AI is searching. When we evaluate the board, we
will always use whowillMove's values, which are chesspower[whowillMove], distance[whowillMove][type][dis]

PS. there are relevant changes on Pieces class as well. 
