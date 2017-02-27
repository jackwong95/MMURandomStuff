package SaveUtil;

import java.io.*;
import Builder.Saver;
/**
 * Decoder (the loader)
 * 
 * @author Ng Chen Hon
 *
 */
public class Decoder 
{
	private Decoder(){}
	
	private static Saver save = null;

    /**
     * remove the current saver
     * 
     * @return boolean
     * 
     */	
	public static boolean isSaveReady()
	{
		return save==null;
	}

    /**
     * get the current saver instance 
     * 
     * @return instance of Saver
     * 
     */	
	public static Saver getSave()
	{
		return save;
	}

    /**
     * remove the current saver
     * 
     * @return void
     * 
     */	
	public static void removeBuff()
	{
		save = null;
	}
    /**
     * output the status of the input file 
     * 
     * @param Takes in a string of file name where it can be any name
     * 
     * @return boolean
     */
	public static boolean loadSave(String fileName)
	{
		try{
			FileInputStream fileInput = new FileInputStream(fileName);
			ObjectInputStream objInput = new ObjectInputStream(fileInput);
			
			save = (Saver)objInput.readObject();
			objInput.close();
			fileInput.close();
			return true;
		}catch(IOException e){
			e.printStackTrace();
		}catch(ClassNotFoundException c){
			c.printStackTrace();
		}
		return false;
	}
}
