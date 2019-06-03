package com.salesforce.app;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.sql.*;

public class App {
    public static void main(String[] args) {
        String[] instance_name = {"first", "second", "third"};
        String[] last_updated = {"12may","22may","12may"};

        try {
            FileWriter fw = new FileWriter("result.txt");
            BufferedWriter br=new BufferedWriter(fw);
            for (int index=0;index<instance_name.length;index++) {
                System.out.println("Name of instance:" + instance_name[index]);

                //extract build info of this instance in result.txt (JSON) file

                br.write(instance_name[index]+"-"+last_updated[index]);

                br.newLine();



            }

            br.close();

            //retrive data in hashmap

            DataRetrieve obj=new DataRetrieve("result.txt");
            HashMap map=obj.getData();

            //traversing map


            for(Object name:map.keySet()) {
                System.out.println("Key: " + name + " Value: " + map.get(name));


                //insert in dataabse


                try {
                    Class.forName("com.mysql.jdbc.Driver");
                    Connection con = DriverManager.getConnection(
                            "jdbc:mysql://localhost:3306/first", "root", "");
//here first is database name, root is username and password
                    Statement stmt = con.createStatement();
                    stmt.executeUpdate("insert into user values ('"+name+"','"+map.get(name)+"')");
                    con.close();
                } catch (Exception e) {
                    System.out.println(e);
                }
            }





        } catch (IOException e) {
            e.printStackTrace();
        }





    }
}


