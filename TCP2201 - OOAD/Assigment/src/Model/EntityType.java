package Model;

import java.awt.Color;
import java.awt.Font;

import Game.GlobalSetting;
/**
 * Each type of entity in the board
 * 
 * @author Wong Tiong Kiat and Choe Choon Ho
 *
 */
public enum EntityType
{
	EMPTY(GlobalSetting.COMPLETE_WHITE_TRANSPARENT, Color.WHITE, " ", "EMPTY")
	, PLAYER1(GlobalSetting.COMPLETE_WHITE_TRANSPARENT, Color.RED, " ", "PLAYER1"), 
	PLAYER2(GlobalSetting.COMPLETE_WHITE_TRANSPARENT, Color.BLUE, " ", "PLAYER2"),
	BULLET(GlobalSetting.COMPLETE_WHITE_TRANSPARENT, Color.ORANGE, " ", "BULLET");

	private final Font font;
	private final Color foreGround;
	private final Color backGround;
	private final String text;
	private final String uniqueIdentifier;
    /**
     * get the font of the entity type
     *
     * @return EntityActionSequence
     */
	public Font getFont () {return font;}
    /**
     * get the background color of the entity type
     *
     * @return Color
     */
	public Color getForegroundColor () {return foreGround;}
    /**
     * get the foreground color of the entity type
     *
     * @return Color
     */
	public Color getBackgroundColor () {return backGround;}
    /**
     * get the string of text
     *
     * @return String
     */
	public String getText () {return text;}
    /**
     * get the string that uniquely identifies this entity type
     *
     * @return String
     */
	public String getIdentifier () {return uniqueIdentifier;}
	
	EntityType(Color foreColor, Color backColor, String text, String uniqueType)
	{
		this.font = GlobalSetting.tankTempFont;
		this.foreGround = foreColor;
		this.backGround = backColor;
		this.text = text;
		this.uniqueIdentifier = uniqueType;
	}
	
};
