package View;

import javax.swing.*;
import java.awt.Dimension;
/**
 * 
 * Each of the button in view is a custombutton
 * 
 * @author Lim Yun Shen
 *
 */
public class CustomButton extends JButton
{
	private static final long serialVersionUID = -327849069472490427L;
    /**
     * Constructor for objects of class custom game action button, where each action button represents an action
     * 
     * @param  String rerepsenting the type of text this button will display
     * @param  String description for the type of button
     * @param  Integer width of this button
     * @param  Integer height of this button
     */
    public CustomButton(String text, String description, int width, int height)
    {
        this.setPreferredSize(new Dimension (width, height));
        this.setText(text);
        this.setToolTipText(description);
    }
}
