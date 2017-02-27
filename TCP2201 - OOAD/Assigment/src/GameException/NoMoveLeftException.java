package GameException;
/**
 * Exception class used when there is an attempt to remove when the action sequence is already empty
 * 
 * @author Wong Tiong Kiat and Choe Choon Ho
 *
 */
public class NoMoveLeftException extends Exception 
{

	private static final long serialVersionUID = -8518708535292162130L;
	
    /**
     * Constructor for NoMoveLeftException
     * 
     */
	public NoMoveLeftException() 
	{
    }
	
    /**
     * Constructor for NoMoveLeftException
     * @param string of message to be displayed
     */
    public NoMoveLeftException(String message) 
    {
        super(message);
    }
    
    /**
     * Constructor for NoMoveLeftException
     * @param throwable 
     */
    public NoMoveLeftException(Throwable cause) 
    {
        super(cause);
    }
    
    /**
     * Constructor for NoMoveLeftException
     * @param string of message to be displayed
     * @param throwable 
     */
    public NoMoveLeftException(String message, Throwable cause) 
    {
        super(message, cause);
    }

}
