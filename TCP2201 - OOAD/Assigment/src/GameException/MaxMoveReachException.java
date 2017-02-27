package GameException;
/**
 * Exception class used when there is an attempt to add maximum size of what action sequence can hold
 * 
 * @author Wong Tiong Kiat
 *
 */
public class MaxMoveReachException extends Exception 
{
	private static final long serialVersionUID = -3314209392826802383L;

    /**
     * Constructor for MaxMoveReachException
     * 
     */
	public MaxMoveReachException() 
	{
    }
	
    /**
     * Constructor for MaxMoveReachException
     * @param string of message to be displayed
     */
    public MaxMoveReachException(String message) 
    {
        super(message);
    }
    
    /**
     * Constructor for MaxMoveReachException
     * @param throwable 
     */
    public MaxMoveReachException(Throwable cause) 
    {
        super(cause);
    }
    
    /**
     * Constructor for MaxMoveReachException
     * @param string of message to be displayed
     * @param throwable 
     */
    public MaxMoveReachException(String message, Throwable cause) 
    {
        super(message, cause);
    }

}