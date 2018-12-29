package gui;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.Line2D;
import java.math.*;
import java.util.Scanner;

/**
 * View
 * @author Li, Shuangquan
 */

public class UI extends JFrame{



    private String[] data;

    public UI(String[] data){
        this.data = data;
    }




    public Line2D lineGen(double x0, double y0, int width, int degrees){

        Line2D line = null;

        if(degrees <= 90){
            line = new Line2D.Double(x0, y0, (x0-width), (y0-width));
            System.out.println("line1: "+((Line2D.Double) line).x2+" "+((Line2D.Double) line).y2);
        }else{
            line = new Line2D.Double(x0, y0, (x0+width), (y0-width));
            System.out.println("line2: "+((Line2D.Double) line).x2+" "+((Line2D.Double) line).y2);
        }




        return line;
    }





    public double coordinateYGen(int distance, double angle){


            double y = (Math.sin(angle) * distance);

            System.out.println("y: "+(275+y));
            System.out.println("y:  "+(y));
            return 275-y;


    }

    public double coordinateXGen(int distance, double angle){

            double x =  (Math.cos(angle) * distance);
            System.out.println("x: "+(x+250));
            System.out.println("x: "+(x));
            return 250+x;
    }

    public double converter(int angle){
        return angle * (Math.PI/180.0);

    }


    public void drawOval(int index){
        Graphics g = this.getGraphics();
        g.setColor(Color.red);

        Scanner scan = new Scanner(data[index]);

        int angle = scan.nextInt();
        int distance = scan.nextInt();
        int width = scan.nextInt();
        System.out.println("A: "+angle);

        g.drawOval((int)coordinateXGen(distance,converter(angle)),(int)coordinateYGen(distance, converter(angle)), width, width);
    }




    public void GUI(){

        setTitle("Reboot GUI");
        JPanel panel = new JPanel();
        JLabel label = new JLabel();



        JButton button = new JButton("start");

        //DrawLine line = new DrawLine();




        this.setResizable(false);

        ImageIcon img = new ImageIcon("./image.jpg");



        this.setSize(500,320);

        label.setIcon(img);
        panel.add(label);
        panel.add(button);
        //button.setBounds(30,30,20,20);
        //button.setLocation(200,500);




        add(panel);


        button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {

                System.out.println("You clicked the button");



                for(int i = 0; i < data.length; i++){

                    drawOval(i);

                }


                //drawOval(0);

            }
        });


        setExtendedState(JFrame.NORMAL);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);






    }


}
