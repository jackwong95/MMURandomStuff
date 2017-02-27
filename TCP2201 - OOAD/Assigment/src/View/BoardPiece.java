package View;

import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.Border;

import Game.GlobalSetting;
import Model.EntityType;
/**
 * Each board piece (cell) of the board
 * 
 * @author Wong Tiong Kiat and Choe Choon Ho
 *
 */
public class BoardPiece extends JPanel
{

	private static final long serialVersionUID = 1L;
	public static final EntityType EMPTY = EntityType.EMPTY;
	public static final EntityType PLAYER1 = EntityType.PLAYER1;
	public static final EntityType PLAYER2 = EntityType.PLAYER2;
	public static final EntityType BULLET = EntityType.BULLET;
	
	private CardLayout layout;
	
	private BoardPieceLabel empty, bullet;
	private BoardPieceImage player1, player2;
	private BoardPieceImage player1Up, player2Up;
	private BoardPieceImage player1Down, player2Down;
	private BoardPieceImage player1Left, player2Left;
	private BoardPieceImage player1Right, player2Right;

    /**
     * Constructor for objects of class BoardPiece
     * 
     */
	public BoardPiece()
	{
		empty = new BoardPieceLabel(EMPTY.getForegroundColor(), EMPTY.getBackgroundColor(), EMPTY.getFont(), EMPTY.getText());
		
		bullet = new BoardPieceImage(BULLET.getForegroundColor(), BULLET.getBackgroundColor(), BULLET.getFont()
				, BULLET.getText(), GlobalSetting.PLAYER_PROJECTILE_IMAGE_PATH);
		player1 = new BoardPieceImage(PLAYER1.getForegroundColor(), PLAYER1.getBackgroundColor(), PLAYER1.getFont()
				, PLAYER1.getText(), GlobalSetting.PLAYER_TANK_IMAGE_PATH);
		player1Up = new BoardPieceImage(PLAYER1.getForegroundColor(), PLAYER1.getBackgroundColor(), PLAYER1.getFont()
				, PLAYER1.getText(), GlobalSetting.PLAYER_TANK_IMAGE_PATH_UP);
		player1Down = new BoardPieceImage(PLAYER1.getForegroundColor(), PLAYER1.getBackgroundColor(), PLAYER1.getFont()
				, PLAYER1.getText(), GlobalSetting.PLAYER_TANK_IMAGE_PATH_DOWN);
		player1Left = new BoardPieceImage(PLAYER1.getForegroundColor(), PLAYER1.getBackgroundColor(), PLAYER1.getFont()
				, PLAYER1.getText(), GlobalSetting.PLAYER_TANK_IMAGE_PATH_LEFT);
		player1Right = new BoardPieceImage(PLAYER1.getForegroundColor(), PLAYER1.getBackgroundColor(), PLAYER1.getFont()
				, PLAYER1.getText(), GlobalSetting.PLAYER_TANK_IMAGE_PATH_RIGHT);
		

		player2 = new BoardPieceImage(PLAYER2.getForegroundColor(), PLAYER2.getBackgroundColor(), PLAYER2.getFont()
				, PLAYER2.getText(), GlobalSetting.PLAYER_TANK_IMAGE_PATH);
		player2Up = new BoardPieceImage(PLAYER2.getForegroundColor(), PLAYER2.getBackgroundColor(), PLAYER2.getFont()
				, PLAYER2.getText(), GlobalSetting.PLAYER_TANK_IMAGE_PATH_UP);
		player2Down = new BoardPieceImage(PLAYER2.getForegroundColor(), PLAYER2.getBackgroundColor(), PLAYER2.getFont()
				, PLAYER2.getText(), GlobalSetting.PLAYER_TANK_IMAGE_PATH_DOWN);
		player2Left = new BoardPieceImage(PLAYER2.getForegroundColor(), PLAYER2.getBackgroundColor(), PLAYER2.getFont()
				, PLAYER2.getText(), GlobalSetting.PLAYER_TANK_IMAGE_PATH_LEFT);
		player2Right = new BoardPieceImage(PLAYER2.getForegroundColor(), PLAYER2.getBackgroundColor(), PLAYER2.getFont()
				, PLAYER2.getText(), GlobalSetting.PLAYER_TANK_IMAGE_PATH_RIGHT);

		layout = new CardLayout();
		this.setLayout(layout);

		this.add(empty, EMPTY.getIdentifier());
		
		this.add(player1, PLAYER1.getIdentifier());
		this.add(player1Up, "player1up");
		this.add(player1Down, "player1down");
		this.add(player1Left, "player1left");
		this.add(player1Right, "player1right");

		this.add(player2, PLAYER2.getIdentifier());
		this.add(player2Up, "player2up");
		this.add(player2Down, "player2down");
		this.add(player2Left, "player2left");
		this.add(player2Right, "player2right");
		
		this.add(bullet, BULLET.getIdentifier());
		
		switchType(EMPTY);
		
	}
    /**
     * switch the current cell to a specific image type
     *
     * @param EntityType of type to switch the image to
     * 
     * @return void
     */
	public void switchType(EntityType type)
	{
		if(type != null)
		{
			layout.show(this, type.getIdentifier());
		}
		else
		{
			layout.show(this, EMPTY.getIdentifier());
		}
	}
    /**
     * overloaded method for switchig current cell to a specific image
     *
     * @param String type of image to switch to
     * 
     * @return void
     */
	public void switchType(String type)
	{
		if(type != null)
		{
			layout.show(this, type);
		}
		else
		{
			layout.show(this, EMPTY.getIdentifier());
		}
	}
	
}

class BoardPieceLabel extends JLabel
{

	private static final long serialVersionUID = 1L;

    /**
     * Constructor for objects of class BoardPieceLabel
     * 
     * @param Color of the foreground of the jlabel
     * @param Color of the background of the jlabel
     * @param Font type of the jlabel
     * @param String text of the jlabel
     * 
     */
	public BoardPieceLabel(Color foreGround, Color backGround, Font font, String text)
	{
		this.setHorizontalAlignment(SwingConstants.CENTER);
		this.setPreferredSize(new Dimension(GlobalSetting.GAME_CELL_WIDTH, GlobalSetting.GAME_CELL_HEIGHT));
        
		Border borderColor = BorderFactory.createLineBorder(Color.BLACK);
        this.setBorder(borderColor);
        
        this.setForeground(foreGround);
        this.setBackground(backGround);
        this.setOpaque(true);
        
        this.setFont(font);
        this.setText(text);
	}
	
}

class BoardPieceImage extends BoardPieceLabel
{
	private static final long serialVersionUID = 1L;

    /**
     * Constructor for objects of class BoardPieceImage which inherits from BoardPieceLabel
     * 
     * @param Color of the foreground of the jlabel
     * @param Color of the background of the jlabel
     * @param Font type of the jlabel
     * @param String text of the jlabel
     * @param String image path of the jlabel
     * 
     */
	public BoardPieceImage(Color foreGround, Color backGround, Font font, String text, String imagePath)
	{
		super(foreGround, backGround, font, text);

        BufferedImage image;
		try 
		{
			image = ImageIO.read(new File(imagePath));
	        this.setIcon(new ImageIcon(image));
	        this.setOpaque(true);
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	}
	
}