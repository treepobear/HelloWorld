import javafx.application.*;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Window extends Application{
    @Override
    public void start(Stage primaryStage) throws Exception {
        Scene scene = new Scene(new View(),630,460);
        primaryStage.setTitle("Connect 4");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

//    public static void main(String[] args){
//        launch(args);
//    }

}
