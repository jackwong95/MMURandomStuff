package SaveUtil;

import java.io.*;
import Builder.Saver;
/**
 * Encoder(the saver)
 * 
 * @author Ng Chen Hon
 *
 */
public class Encoder 
{
	private Encoder(){}
    /**
     * output the status of the output file 
     * 
     * @param Takes in a type of save instance to be save
     * @param Takes in a string of file name where it can be any name
     * 
     * @return boolean
     */
	public static boolean outputSave(Saver save, String fileName)
	{
		try
		{
			FileOutputStream fileOutput = new FileOutputStream(fileName);
			ObjectOutputStream ObjOutput = new ObjectOutputStream(fileOutput);
			
			ObjOutput.writeObject(save);
			ObjOutput.close();
			fileOutput.close();
			System.out.println("Saved file at : " + fileName);
			return true;
		}catch(IOException e){
			e.printStackTrace();
		}
		return false;
	}
}
