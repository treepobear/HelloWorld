import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.layout.Pane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.text.Text;

public class View extends Pane{
    private Core core;
    private Pane board=new Pane();
    private HBox dropBox= new HBox();
    private VBox vicText = new VBox();
    private VBox toolBox=new VBox();
    private int winner=0;
    public View(){
        core=new Core(1);
        board.setLayoutX(0);
        board.setLayoutY(30);
        dropBox.setLayoutX(0);
        dropBox.setLayoutY(0);
        dropBox.setSpacing(10);
        dropBox.setPadding(new Insets(10,10,10,10));
        vicText.setPadding(new Insets(10,10,10,10));
        vicText.setSpacing(5);
        vicText.setLayoutX(520);
        vicText.setLayoutY(30);
        toolBox.setSpacing(10);
        toolBox.setLayoutX(500);
        toolBox.setLayoutY(350);
        toolBox.setPadding(new Insets(10,10,10,10));
        drawPlainDisc();
        drawDropButton();
        drawToolButton();
        this.getChildren().addAll(board,dropBox,vicText,toolBox);
    }
    private void drawPlainDisc() {
        //画board上的圈圈
        for (int r = 0; r < 6; r++) {
            for (int c = 0; c < 7; c++) {
                Circle circle = new Circle();
                circle.setRadius(30);
                circle.setCenterY(10 * (r + 1) + 30 * (2 * r + 1));
                circle.setCenterX(10 * (c + 1) + 30 * (2 * c + 1));
                circle.setStroke(Color.BLACK);
                circle.setFill(Color.WHITE);
                board.getChildren().add(circle);
            }
        }
    }
    private void drawDropButton(){
        //画drop的button
        for(int i=0;i<7;i++){
            Button btdrop=new Button("DROP");
            btdrop.setPrefSize(60,20);
            final int iCol=i;//当所在的方法的形参需要被内部类里面使用时，该形参必须为final
            btdrop.setOnAction(new EventHandler<ActionEvent>() {
                @Override
                public void handle(ActionEvent event){
                    for(int r=5;r>=0;r--){
                        if(core.core[r][iCol]==-1) {
                            drawDisc(r, iCol);
                            winner=core.drop(iCol);
                            break;
                        }
                    }
                    System.out.println(winner);
                    if(winner!=0){
                        if(winner==1){
                            Text redwins = new Text("Red Wins!");
                            vicText.getChildren().add(redwins);

                        }else if(winner==2){
                            Text blackwins = new Text("Black Wins!");
                            vicText.getChildren().add(blackwins);
                        }
                        board.getChildren().clear();
                        drawPlainDisc();
                        core=new Core(1);
                    }

                }
            });
            dropBox.getChildren().add(btdrop);
        }

    }

    private void drawToolButton(){
        Button restart=new Button("RESTART");
        restart.setPrefSize(100,30);
        restart.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                board.getChildren().clear();
                drawPlainDisc();
                core=new Core(1);
            }
        });
        Button help=new Button("HELP");
        help.setPrefSize(100,30);
        help.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                Alert help = new Alert(Alert.AlertType.INFORMATION);
                help.setHeaderText("Rules and Cautions");
                help.setTitle("Help");
                help.setContentText(
                        "Connect 4 is a two-player connection game in which the players take turns dropping colored discs from the top into the board.\n" +
                                "The discs fall straight down, occupying the lowest available space within the column. \n" +
                                "The objective of the game is to be the first to form a horizontal, vertical, or diagonal line of four of one's own discs.\n\n"+
                                "Code by TreepoBear.\n"+
                                "You can connect me through VX:cynthia9375 if you want.");
                help.showAndWait();
            }
        });
        toolBox.getChildren().addAll(restart,help);
    }

    private void drawDisc(int row,int col) {
        Circle disc=new Circle();
        disc.setCenterY(10*(row+1)+30*(2*row+1));
        disc.setCenterX(10*(col+1)+30*(2*col+1));
        disc.setRadius(30);
        if(core.player==1)
            disc.setFill(Color.RED);
        else if(core.player==2)
            disc.setFill(Color.BLACK);
        board.getChildren().add(disc);
    }
}


