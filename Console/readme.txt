5/3/2016

Board�������whowillMove, ��ָ����Ҫ���ӵ��ˡ�curplayer����AI��˼�����仯������ʱ������whowillmove���player�ķ���ϵͳ��
���⣬Piece��ÿ������ֵ���������ˡ�һ����Player0�ķ���ϵͳ����һ����player1�ķ���ϵͳ��

Add whowillMove to Board, which indicate the real player that will move next round. Curplayer is used in the thinking process, so that it will changes when the AI is searching. When we evaluate the board, we
will always use whowillMove's values, which are chesspower[whowillMove], distance[whowillMove][type][dis]

In addition, there are relevant changes on Pieces class as well. 