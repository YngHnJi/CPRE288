package gui;


import gui.UI;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/**
 * Main program
 * @author Li,Shuangquan
 */

public class Main {

    /**
     * main method, execute the pogrom
     * @param args
     */
    public static void main(String[] args){

        int objectCounter  = 0;
        String str = "";
        int i = 0;



        //ile data = new File("./Data.txt");

        try {
            Scanner scan = new Scanner(new File("./Data.txt"));

            while(scan.hasNext()){

                str = scan.nextLine();

                //System.out.println(scan.nextInt());
                objectCounter++;

                System.out.println(str);

            }

            scan.close();

        }catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        //Scanner scan = new Scanner(new File("./Data.txt"));

        System.out.println("Num of obj: "+objectCounter);


        String rawData[] = new String[objectCounter];


        try {
            Scanner scan = new Scanner(new File("./Data.txt"));

            while(scan.hasNext()){

                rawData[i] = scan.nextLine();
                i++;

            }

            scan.close();

        }catch (FileNotFoundException e) {
            e.printStackTrace();
        }


        System.out.println(rawData[0]);

        UI u = new UI(rawData);
        u.GUI();



    }


}
