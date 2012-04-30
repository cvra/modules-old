using System;
using System.Collections.Generic;
using System.Text;
using System.IO.Ports;
using System.Threading;
using System.Windows.Forms;
using System.IO;

namespace grinlib.PortCom
{
  /// <summary>
  /// Gestion du port série
  /// </summary>
  public class clPortCom
  {
    private Form p_ParentForm;

    /// <summary>
    /// Forme parente pour synchornisation
    /// </summary>
    public Form ParentForm
    {
      get { return p_ParentForm; }
      set { p_ParentForm = value; }
    }

    private SerialPort ComSerial = null;
    //private int CmtReceivdTimeOut = 0;
    //	private const bool UseInterrup = true;
    private List<byte[]> Data2Send;
    private bool threadIsRunning = false;
    Thread TimerDataSend;

    /// <summary>
    /// Messages des évenements
    /// </summary>
    public enum ETAT_CONN
    {
      /// <summary>
      /// Un client est connecté
      /// </summary>
      CLIENT_CONNECTED,
      /// <summary>
      /// Un client est déconnect
      /// </summary>
      CLIENT_DISCONNECTED,
      /// <summary>
      /// Des données sont reçues
      /// </summary>
      DATA_RECEIVED,
      /// <summary>
      /// Des données ont été envoyées
      /// </summary>
      DATA_SENT,
      /// <summary>
      /// Attente d'un client
      /// </summary>
      WAITING_CLIENT,
      /// <summary>
      /// Une erreure est apparue, voir e.Data
      /// </summary>
      ERROR
    }

    /// <summary>
    /// Destructeur
    /// </summary>
    ~clPortCom()
    {

    }

    /// <summary>
    /// A appeller lors de la fermeture du programme
    /// </summary>
    public void End()
    {
      Disconnect();

      if (TimerDataSend != null)
      {
        threadIsRunning = false;

        for (int i = 0; i < 50; i++)
        {
          System.Threading.Thread.Sleep(100);
          if (TimerDataSend.IsAlive == false)
            return;
        }

        try
        {
          TimerDataSend.Abort();
        }
        catch (System.Threading.ThreadAbortException ex)
        {
          Console.WriteLine("***~clPortCom ThreadAbortException " + ex.Message);
        }
        System.Threading.Thread.Sleep(1000);
      }
    }

    /// <summary>
    /// Constructeur
    /// </summary>
    public clPortCom()
    {
      ComSerial = new SerialPort();

      threadIsRunning = true;
      TimerDataSend = new Thread(EventSendTimer);
      TimerDataSend.Name = "PortCom DataSend";
      TimerDataSend.Priority = ThreadPriority.Highest;
      TimerDataSend.Start();
    }

    /// <summary>
    /// Connection à un port série
    /// </summary>
    /// <param name="NumPort">Numéro sous la forme "COM1"</param>
    /// <param name="Baudrate">Débit en baud (ex: "57600")</param>
    public void Connect(string NumPort, int Baudrate)
    {
      Console.WriteLine("***Connect Start");
      try
      {
        if (ComSerial != null && ComSerial.IsOpen)
        {
          ComSerial.Close();
          System.Threading.Thread.Sleep(1000);
        }

        Data2Send = new List<byte[]>();

        //				ComSerial = new SerialPort(NumPort, Baudrate, Parity.None, 8, StopBits.One);
        ComSerial.PortName = NumPort;
        ComSerial.BaudRate = Baudrate;
        ComSerial.Parity = Parity.None;
        ComSerial.DataBits = 8;
        ComSerial.StopBits = StopBits.One;

        //ComSerial.ReceivedBytesThreshold = 1;
        ComSerial.ReadTimeout = 2000;
        ComSerial.WriteTimeout = 2000;
        //ComSerial.ErrorReceived += new SerialErrorReceivedEventHandler(ComSerial_ErrorReceived);
        ComSerial.Open();
        //System.Threading.Thread.Sleep(1000);
        //if (UseInterrup)
        //{
        //  ComSerial.DataReceived += new SerialDataReceivedEventHandler(ComSerial_DataReceived);
        //}

        ComSerial.DiscardInBuffer();

        //if (!UseInterrup)
        //{
        //  TimerDataCheck = new Thread(EventTimer);
        //  TimerDataCheck.Name = "PortCom DataCheck";
        //  //TimerDataCheck.Priority = ThreadPriority.Lowest;
        //  CmtReceivdTimeOut = 0;
        //  TimerDataCheck.Start();
        //}
        OnEventOccure(ETAT_CONN.CLIENT_CONNECTED, "Connected", new byte[1]);

      }
      catch (Exception ex)
      {
        Console.WriteLine("***Connect Exception " + ex.Message);
        //throw e;
        Disconnect();
        OnEventOccure(ETAT_CONN.ERROR, ex.Message, new byte[1]);
      }
      Console.WriteLine("***Connect End");
    }

    //void ComSerial_DataReceived(object sender, SerialDataReceivedEventArgs e)
    //{
    //  switch (e.EventType)
    //  {
    //    case SerialData.Chars:
    //      int NbToRead = Math.Min(ComSerial.BytesToRead, 2000);
    //      byte[] NewByte = new byte[NbToRead];

    //      int NbByte = ComSerial.Read(NewByte, 0, NbToRead);
    //      // Envois des données

    //      OnEventOccure(ETAT_CONN.DATA_RECEIVED, System.Text.Encoding.UTF8.GetString(NewByte, 0, NbToRead), NewByte);

    //      break;
    //    case SerialData.Eof:
    //      break;
    //    default:
    //      break;
    //  }
    //}

    //void ComSerial_ErrorReceived(object sender, SerialErrorReceivedEventArgs e)
    //{
    //  OnEventOccure(ETAT_CONN.ERROR, e.ToString(), new byte[1]);
    //}

    /// <summary>
    /// Déconnection
    /// </summary>
    public void Disconnect()
    {
      Console.WriteLine("***Disconnect Start");

      if (ComSerial != null)
      {
        try
        {
          OnEventOccure(ETAT_CONN.CLIENT_DISCONNECTED, "Disconnected", new byte[1]);

          System.Threading.Thread.Sleep(100);
          ComSerial.Close();
          //ComSerial.Dispose();
        }
        catch (Exception ex)
        {
          Console.WriteLine("Disconnect Exception2 " + ex.Message);
        }
      }
      Console.WriteLine("***Disconnect End");
      //if (TimerDataCheck != null)
      //	TimerDataCheck.Abort();
    }

    /// <summary>
    /// Contrôle si le port série est ouvert
    /// </summary>
    /// <returns>Le port est ouvert ou non</returns>
    /// 

    public bool IsOpen
    {
      get
      {
        if (ComSerial != null)
        {
          return ComSerial.IsOpen;
        }
        return false;
      }

    }

    int NbToRead;
    int NbByte;
    byte[] NewByte;
    int CmtError;
    private void EventSendTimer() //(Object stateInfo)
    {
      try
      {
        while (threadIsRunning)
        {
          Thread.Sleep(30);

          if (ComSerial != null && ComSerial.IsOpen)
          {
            try
            {
              NbToRead = ComSerial.BytesToRead;
              if (NbToRead > 0)
              {
                NewByte = new byte[NbToRead];

                NbByte = ComSerial.Read(NewByte, 0, NbToRead);
                // Envois des données
                CmtError = 0;
                OnEventOccure(ETAT_CONN.DATA_RECEIVED, System.Text.Encoding.UTF8.GetString(NewByte, 0, NbToRead), NewByte);
              }


              while (Data2Send.Count > 0)
              {
								this.ComSerial.Write(Data2Send[0], 0, Data2Send[0].Length);
                /*for (int i = 0; i < Data2Send[0].Length; i++)
                {
                  this.ComSerial.Write(Data2Send[0], i, 1);
                  System.Threading.Thread.Sleep(1);
                }*/
                Data2Send.RemoveAt(0);
                CmtError = 0;
              }
            }
            catch (InvalidOperationException ex)
            {
              Console.WriteLine("EventSendTimer InvalidOperationException " + ex.Message);
              CmtError++;

              if (CmtError > 10)
                Disconnect();
            }
            catch (IOException ex)
            {
              Console.WriteLine("EventSendTimer IOException " + ex.Message);
              CmtError++;

              if (CmtError > 10)
                Disconnect();
            }
            catch (ArgumentNullException ex)
            {
              Console.WriteLine("EventSendTimer ArgumentNullException " + ex.Message);
              CmtError++;

              if (CmtError > 10)
                Disconnect();
            }
            catch (TimeoutException ex)
            {
              Console.WriteLine("EventSendTimer TimeoutException " + ex.Message);
              CmtError++;

              if (CmtError > 10)
                Disconnect();
            }
            catch (ArgumentOutOfRangeException ex)
            {
              Console.WriteLine("EventSendTimer ArgumentOutOfRangeException " + ex.Message);
              CmtError++;

              if (CmtError > 10)
                Disconnect();
            }
            catch (ArgumentException ex)
            {
              Console.WriteLine("EventSendTimer ArgumentException " + ex.Message);
              CmtError++;

              if (CmtError > 10)
                Disconnect();
            }
          }
        }
      }
      catch (ThreadAbortException ex)
      {
        Console.WriteLine("EventSendTimer ThreadAbortException " + ex.Message);
      }
    }

    /// <summary>
    /// Envois de donnée
    /// </summary>
    /// <param name="Data">Chaine à envoyer</param>
    /// <returns>Vrais si ok</returns>
    public bool Send(string Data)
    {
      try
      {
        if (Data.Length > 0 && this.ComSerial != null)
        {
          byte[] msg = System.Text.Encoding.UTF8.GetBytes(Data);
          Data2Send.Add(msg);
        }

        return true;
      }
      catch (Exception ex)
      {
        Console.WriteLine("Send Exception" + ex.Message);
        return false;
      }
    }

    /// <summary>
    /// Envois de donnée
    /// </summary>
    /// <param name="Data">Données en byte</param>
    /// <returns></returns>
    public bool Send(byte[] Data)
    {
      if (Data2Send == null)
        return false;
      try
      {
        if (Data.Length > 0 && this.ComSerial != null)
        {
          Data2Send.Add(Data);
        }

        return true;
      }
      catch (Exception ex)
      {
        Console.WriteLine("SendByte Exception" + ex.Message);
        return false;
      }
    }

    // **************************Evénements de la classe*************************
    /// <summary>
    /// Evenement du port série
    /// </summary>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    public delegate void EventDelegate(object sender, EventEventArgs e);
    /// <summary>
    /// Valeurs de l'évenement
    /// </summary>
    public class EventEventArgs : EventArgs
    {
      /// <summary>
      /// Création des données d'évenement
      /// </summary>
      /// <param name="typeevent"></param>
      /// <param name="data"></param>
      /// <param name="dataByte"></param>
      public EventEventArgs(ETAT_CONN typeevent, string data, byte[] dataByte)
      {
        this.TypeEvent = typeevent;
        this.Data = data;
        this.DataByte = dataByte;
      }
      /// <summary>
      /// Valeurs par défaut
      /// </summary>
      public EventEventArgs()
      {
        this.TypeEvent = 0;
        this.Data = "";
        this.DataByte = null;
      }

      /// <summary>
      /// Données en string
      /// </summary>
      public string Data;
      /// <summary>
      /// Données en byte
      /// </summary>
      public byte[] DataByte;
      /// <summary>
      /// Type d'évenement
      /// </summary>
      public ETAT_CONN TypeEvent;
    }

    /// <summary>
    /// Evénement du port série
    /// </summary>
    public event EventDelegate OnEvent;
    /// <summary>
    /// Evénement du port série
    /// </summary>
    /// <param name="TypeEvent"></param>
    /// <param name="Data"></param>
    /// <param name="DataByte"></param>
    protected virtual void OnEventOccure(ETAT_CONN TypeEvent, string Data, byte[] DataByte)
    {
      if (OnEvent != null)
      {
        EventEventArgs e = new EventEventArgs(TypeEvent, Data, DataByte);

        if (p_ParentForm == null)
        {
          OnEvent(this, e);
        }
        else
        {
          p_ParentForm.Invoke(OnEvent, new object[] { this, e });
        }
      }
    }
  }
}
