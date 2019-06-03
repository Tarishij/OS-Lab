package com.salesforce.app;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

public class DataRetrieve {
    private HashMap hm;
    private String filename;

    public DataRetrieve(String file){
        hm=new HashMap<String,String>();
        filename=file;

    }

    public HashMap getData(){
        try {
            BufferedReader br = new BufferedReader(new FileReader("result.txt"));
            String line=br.readLine();


            //parsing data

            while(line!= null){
                System.out.println(line);
                String[] content=line.split("-");
                hm.put(content[0],content[1]);


                //read next
                line=br.readLine();
            }
            br.close();



        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }


        return hm;

    }



}
