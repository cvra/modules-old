using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Threading;

namespace lib.TCPClient
{
	/// <summary>
	/// Use TCP as client
	/// </summary>
	public class clTCPClient
	{
		// **************************Variables de la classe*************************
		//bool p_Connected = false;
		string p_IPServer = "";
		int p_Port = 0;
		TcpClient client = null;
		NetworkStream stream = null;
		Thread Listener;
		private bool Connecting = false;

		/// <summary>
		/// Events type
		/// </summary>
		public enum EtatConn
		{
			/// <summary>
			/// The client is connected
			/// </summary>
			CLIENT_CONNECTED,
			/// <summary>
			/// The client is disconnected
			/// </summary>
			CLIENT_DISCONNECTED,
			/// <summary>
			/// Data is received
			/// </summary>
			DATA_RECEIVED,
			/// <summary>
			/// Data is sent
			/// </summary>
			DATA_SENT,
			/// <summary>
			/// Error
			/// </summary>
			TCP_ERROR
		}
		// **************************Propriétés de la classe*************************
		/// <summary>
		/// State of connexion
		/// </summary>
		public int Connected
		{
			get
			{
				try
				{
					if (client != null && client.Client != null && client.Client.Connected)
						return 2;

					if (Connecting)
						return 1;

					return 0;

				}
				catch
				{
					return 0;
				}
			}
			//set { myVar = value; }
		}


		// **************************Evénements de la classe*************************
		/// <summary>
		/// Event of TCPClient
		/// </summary>
		/// <param name="sender">TCPClient who sent event</param>
		/// <param name="e">Data of event</param>
		public delegate void EventDelegate(object sender, EventEventArgs e);

		/// <summary>
		/// Event class
		/// </summary>
		public class EventEventArgs : EventArgs
		{
			/// <summary>
			/// Init event
			/// </summary>
			/// <param name="typeevent">Type of event</param>
			/// <param name="data">Data of event</param>
			/// <param name="dataByte">Data of event in byte</param>
			public EventEventArgs(EtatConn typeevent, string data, byte[] dataByte)
			{
				this.TypeEvent = typeevent;
				this.DataByte = dataByte;
				this.Data = data; ;
			}
			/// <summary>
			/// Initialisation
			/// </summary>
			public EventEventArgs()
			{
				this.TypeEvent = EtatConn.CLIENT_DISCONNECTED;
				this.Data = "";
			}

			/// <summary>
			/// Data receivd or sent
			/// </summary>
			public string Data;

			/// <summary>
			/// Data in byte
			/// </summary>
			public byte[] DataByte;
			/// <summary>
			/// Type of event
			/// </summary>
			public EtatConn TypeEvent;
		}

		/// <summary>
		/// Event
		/// </summary>
		public event EventDelegate OnEvent;

		/// <summary>
		/// Event
		/// </summary>
		/// <param name="TypeEvent"></param>
		/// <param name="Data"></param>
		/// <param name="DataByte"></param>
		protected virtual void OnEventOccure(EtatConn TypeEvent, string Data, byte[] DataByte)
		{
			if (OnEvent != null)
			{
				EventEventArgs e = new EventEventArgs(TypeEvent, Data, DataByte);

				OnEvent(this, e);
			}
		}

		// **************************Fonctions de la classe*************************
		void Close()
		{
			// Close everything.
			if (stream != null)
				stream.Close();
			stream = null;

			if (client != null)
				client.Close();
			client = null;
		}

		/// <summary>
		/// Connect to a server
		/// </summary>
		/// <param name="IPserver"></param>
		/// <param name="inPort"></param>
		public void Connect(String IPserver, int inPort)
		{
			if (client == null || client.Client.Connected == false)
			{
				p_IPServer = IPserver;
				p_Port = inPort;
				Connecting = true;

				Listener = new Thread(new ThreadStart(this.ThreadListener));
				Listener.Start();
			}
		}

		/// <summary>
		/// Disconnect to the server
		/// </summary>
		public void Disconnect()
		{
			Connecting = false;

			Close();

			OnEventOccure(clTCPClient.EtatConn.CLIENT_DISCONNECTED,"CLIENT_DISCONNECTED",null);
		}

		private void ThreadListener()
		{
			try
			{
				// Create a TcpClient.
				// Note, for this client to work you need to have a TcpServer 
				// connected to the same address as specified by the server, port
				// combination.
				client = new TcpClient(p_IPServer, p_Port);
				// Get a client stream for reading and writing.
				//  Stream stream = client.GetStream();

				stream = client.GetStream();

				OnEventOccure(clTCPClient.EtatConn.CLIENT_CONNECTED, "CONNECTED", null);
				// Receive the TcpServer.response.

				// Buffer for reading data
				Byte[] bytes = new Byte[1024];
				String data = null;

				// String to store the response ASCII representation.
				Int32 i;

				// Read the first batch of the TcpServer response bytes.
				stream.ReadTimeout = 1000000;
				client.ReceiveTimeout = 1000000;
				client.SendTimeout = 1000000;

				Connecting = false;

				while (((i = stream.Read(bytes, 0, bytes.Length)) != 0))
				{
					data = System.Text.Encoding.UTF8.GetString(bytes, 0, i);
					Byte[] r = new Byte[i];
					for (int j = 0; j < i; j++)
					{
						r[j] = bytes[j];
					}
					OnEventOccure(clTCPClient.EtatConn.DATA_RECEIVED, data, r);
				}
			}
			catch (ArgumentNullException e)
			{
				OnEventOccure(clTCPClient.EtatConn.TCP_ERROR, "ArgumentNullException: " + e.Message, null);
				Disconnect();
				//Console.WriteLine("ArgumentNullException: {0}", e);
			}
			catch (SocketException e)
			{
				OnEventOccure(clTCPClient.EtatConn.TCP_ERROR, "SocketException: " + e.Message, null);
				Disconnect();
				//Console.WriteLine("SocketException: {0}", e);
			}
			catch (Exception e)
			{
				OnEventOccure(clTCPClient.EtatConn.TCP_ERROR, "Er: " + e.Message,null);
				Disconnect();
			}

			Disconnect();
			//Console.WriteLine("\n Press Enter to continue...");
		}

		/// <summary>
		/// Close
		/// </summary>
		~clTCPClient()
		{
			Disconnect();
		}

		/// <summary>
		/// Send data to the server
		/// </summary>
		/// <param name="Data"></param>
		/// <returns></returns>
		public bool Send(string Data)
		{
			try
			{
				if (client == null || client.Client == null)
				{
					OnEventOccure(clTCPClient.EtatConn.TCP_ERROR, "Client null ", null);
					return false;
				}
				byte[] msg = System.Text.Encoding.UTF8.GetBytes(Data);

//				client.Client.Send(msg);
				stream.Write(msg, 0, msg.Length);
				stream.Flush();
				OnEventOccure(clTCPClient.EtatConn.DATA_SENT, Data, msg);

				return true;
			}
			catch (Exception e)
			{
				OnEventOccure(clTCPClient.EtatConn.TCP_ERROR, "SocketException: " + e.Message, null);
				Disconnect();

				return false;
			}
		}

		/// <returns></returns>
		public bool Send(byte[] Data)
		{
			try
			{
				if (client == null || client.Client == null)
				{
					OnEventOccure(clTCPClient.EtatConn.TCP_ERROR, "Client null ", null);
					return false;
				}
				//				client.Client.Send(msg);
				
				for (int i = 0; i < Data.Length; i++)
				{
					stream.Write(Data, i, 1);
					stream.Flush();
					System.Threading.Thread.Sleep(10);
				}
				
				OnEventOccure(clTCPClient.EtatConn.DATA_SENT, "", Data);

				return true;
			}
			catch (Exception e)
			{
				OnEventOccure(clTCPClient.EtatConn.TCP_ERROR, "SocketException: " + e.Message, null);
				Disconnect();

				return false;
			}
		}
	}
}
