public class Core {

    public int[][] core;//值为0不可操作；值为-1可操作；值为1红；值为2黑
    public int player;
    public Core(int p){
        core= new int[6][7];//六行七列
        initCore();
        player=p;
    }

    public void initCore(){
        for(int col=0;col<7;col++){
            core[5][col]=-1;//最后一行置-1
        }
    }

    /**
     *落子
     * @param col
     * @return 返回胜利
     */
    public int drop(int col){
        int result=0;
        for(int row=5;row>=0;row--){
            if(core[row][col]==-1){
                core[row][col]=player;
                result=checkVictory(row,col);
                core[row-1][col]=-1;//这一列的上一行置为-1
                if(player==1) player++;
                else player--;
                break;//drop好了就不用再继续了
            }
        }
        return result;
    }

    /**
     *检查是否胜利
     * @param row
     * @param col
     * @return 胜利返回player，没有胜利返回0
     */
    public int checkVictory(int row,int col){
        int vertical=0;//纵向判断
        for(int r=row-3;r<row+4;r++){
            if(r<0||r>=6) continue;
            if(core[r][col]==player) vertical++;
            else vertical=0;
            if(vertical==4) return player;
        }


        int horizonal=0;//横向判断
        for(int c=col-3;c<col+4;c++){
            if(c<0||c>=7) continue;
            if(core[row][c]==player)horizonal++;
            else horizonal=0;
            if(horizonal==4) return player;
        }

        int diagonal1=0;//左上到右下
        for(int r=row-3,c=col-3;r<row+4&&c<col+4;r++,c++){
            if(r<0||c<0||r>=6||c>=7) continue;
            if(core[r][c]==player) diagonal1++;
            else diagonal1=0;
            if(diagonal1==4) return player;
        }

        int diagonal2=0;//左下到右上
        for(int r=row+3,c=col-3;r>row-4&&c<col+4;r--,c++){
            if(r<0||c<0||r>=6||c>=7)
                continue;
            if(core[r][c]==player) diagonal2++;
            else diagonal2=0;
            if(diagonal2==4) return player;
        }

        return 0;
    }
}
