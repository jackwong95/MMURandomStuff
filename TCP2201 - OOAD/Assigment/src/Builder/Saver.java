package Builder;

import java.io.Serializable;
import Model.EntityActionSequence;

/**
 * This saver class includes all the instances of objects, uses a builder design pattern to store each data for the encoder and the decoder class.
 * 
 * Builder - Use to construct this class for the encoder and decoder
 * 
 * @author Ng Chen Hon
 *
 */

public class Saver implements Serializable
{
	/**
	 * 
	 */
	private static final long serialVersionUID = -643322774421123468L;

	public static class SaveBuilder
	{
		private int round;
		private int score;
		
		private EntityActionSequence playerSeq;
		private EntityActionSequence enemySeq;
		/**
		 * constructor for the saver
		 * 
		 */
		public SaveBuilder()
		{
			round = 0;
			score = 0;
			
			playerSeq = null;
			enemySeq = null;
		}
		/**
		 * returns if the builder is ready to be save
		 * 
		 * @return      booelean
		 */
		public Boolean isBuildReady()
		{
			return (playerSeq == null && enemySeq == null);
		}
		
		/**
		 * builder to add score
		 * 
		 * @param integer to add score
		 * @return      SaveBuilder
		 */
		public SaveBuilder addScore(int score)
		{
			this.score = score;
			return this;
		}

		/**
		 * builder to add round
		 * 
		 * @param integer to add round
		 * @return      SaveBuilder
		 */
		public SaveBuilder addRound(int round)
		{
			this.round = round;
			return this;
		}

		/**
		 * builder to add EntityActionSequence of player
		 * 
		 * @param integer to add EntityActionSequence
		 * @return      SaveBuilder
		 */
		public SaveBuilder addPlayerSequence(EntityActionSequence player)
		{
			this.playerSeq = player;
			return this;
		}

		/**
		 * builder to add EntityActionSequence of enemy
		 * 
		 * @param integer to add EntityActionSequence
		 * @return      SaveBuilder
		 */
		public SaveBuilder addEnemySequence(EntityActionSequence enemy)
		{
			this.enemySeq = enemy;
			return this;
		}
		
		public Saver build()
		{
			return new Saver(this);
		}
	}
	
	private final int round;
	private final int score;
	
	private final EntityActionSequence playerSeq;
	private final EntityActionSequence enemySeq;
	
	private Saver(SaveBuilder sb)
	{
		this.round = sb.round;
		this.score = sb.score;
		
		this.playerSeq = sb.playerSeq;
		this.enemySeq = sb.enemySeq;
	}
	
	public int getRound()
	{
		return round;
	}
	
	public int getScore()
	{
		return score;
	}
	
	public EntityActionSequence getPlayerSequence()
	{
		return playerSeq;
	}
	
	public EntityActionSequence getEnemySequence()
	{
		return enemySeq;
	}
}
