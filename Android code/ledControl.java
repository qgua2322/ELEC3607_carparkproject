package com.led.led;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.os.AsyncTask;
import java.io.IOException;
import java.io.InputStream;
import java.util.UUID;
import java.util.Timer;
import java.util.TimerTask;
import android.os.Handler;






public class ledControl extends ActionBarActivity {

    //initialising UI palettes and local variables
    Button btnOn, btnOff, btnDis,btnPay;
    TextView lumn,disp;
    String address = null;
    private ProgressDialog progress;
    BluetoothAdapter myBluetooth = null;
    BluetoothSocket btSocket = null;
    private boolean isBtConnected = false;
    //SPP UUID. Look for it
    static final UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    String calculatedString;
    MyAsyncTask mAsync = null;
    Timer timer = null;
    TimerTask task = null;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        Intent newint = getIntent();
        address = newint.getStringExtra(DeviceList.EXTRA_ADDRESS); //receive the address of the bluetooth device

        //view of the ledControl
        setContentView(R.layout.activity_led_control);

        //call the widgtes
        btnOn = (Button)findViewById(R.id.button2);
        btnOff = (Button)findViewById(R.id.button3);
        btnDis = (Button)findViewById(R.id.button4);
        btnPay = (Button)findViewById(R.id.button5);
        lumn = (TextView)findViewById(R.id.lumn);
        disp = (TextView)findViewById(R.id.textView2);


        new ConnectBT().execute(); //Call the class to connect

        //commands to be sent to bluetooth
        btnOn.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                reserve();//method to reserve

            }
        });

        btnOff.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                leave();   //method to leave
            }
        });

        btnDis.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Disconnect(); //close connection
            }
        });

        btnPay.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                Pay(); //confirm payment
            }
        });


        //timer to trigger the asyncTask for refreshing textview
        final Handler handler = new Handler();
        timer = new Timer();
        task = new TimerTask() {
            @Override
            public void run() {
                handler.post(new Runnable() {
                    public void run() {
                        MyAsyncTask mAsync = new MyAsyncTask();
                        mAsync.execute();
                    }
                });
            }
        };
        timer.schedule(task, 5000, 2000); //execute task after 5s delay and then refresh every 2s




    }


    private class MyAsyncTask extends AsyncTask<String, Void, String> {


        public MyAsyncTask(){

        }

        @Override
        protected String doInBackground(String... params) {
            //Background operation in a separate thread
            //get inputstream via bluetooth from arduino and display on phone
            InputStream tmpIn = null;

            try {
                //Create I/O streams for connection
                tmpIn = btSocket.getInputStream();

            } catch (IOException e) { }

            byte[] buffer = new byte[256];
            int bytes;

            // Keep looping to listen for received messages

                try {
                    bytes = tmpIn.read(buffer);        	//read bytes from input buffer
                    String readMessage = new String(buffer, 0, bytes);
                    // Send the obtained bytes to the UI Activity via handler
                    calculatedString = readMessage;
                } catch (IOException e) {

                }
            return null;
        }

        @Override
        protected void onPostExecute(String result) {
            //Called on Main UI Thread. Executed after the Background operation, allows you to have access to the UI
            disp.setText(calculatedString);


        }

        @Override
        protected void onPreExecute() {
            //Called on Main UI Thread. Executed before the Background operation, allows you to have access to the UI
        }
    }





    private void Disconnect()
    {
        if (btSocket!=null) //If the btSocket is busy
        {
            try
            {
                btSocket.close(); //close connection
            }
            catch (IOException e)
            { msg("Error");}
        }
        finish(); //return to the first layout

    }

    private void leave()
    {
        if (btSocket!=null)//If the btSocket is busy
        {
            try
            {
                btSocket.getOutputStream().write("leave".toString().getBytes());//send 'leave'
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void reserve()
    {
        if (btSocket!=null)//If the btSocket is busy
        {
            try
            {
                btSocket.getOutputStream().write("reserve".toString().getBytes());//send 'reserve'
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    private void Pay()
    {
        if (btSocket!=null)//If the btSocket is busy
        {
            try
            {
                btSocket.getOutputStream().write("pay".toString().getBytes());//send'pay'
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }



    // fast way to call Toast
    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(),s,Toast.LENGTH_LONG).show();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_led_control, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    private class ConnectBT extends AsyncTask<Void, Void, Void>  // UI thread
    {
        private boolean ConnectSuccess = true; //if it's here, it's almost connected

        @Override
        protected void onPreExecute()
        {
            progress = ProgressDialog.show(ledControl.this, "Connecting...", "Please wait!!!");  //show a progress dialog
        }

        @Override
        protected Void doInBackground(Void... devices) //while the progress dialog is shown, the connection is done in background
        {
            try
            {
                if (btSocket == null || !isBtConnected)
                {
                 myBluetooth = BluetoothAdapter.getDefaultAdapter();//get the mobile bluetooth device
                 BluetoothDevice dispositivo = myBluetooth.getRemoteDevice(address);//connects to the device's address and checks if it's available
                 btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(myUUID);//create a RFCOMM (SPP) connection
                 BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                 btSocket.connect();//start connection
                }
            }
            catch (IOException e)
            {
                ConnectSuccess = false;//if the try failed, you can check the exception here
            }
            return null;
        }
        @Override
        protected void onPostExecute(Void result) //after the doInBackground, it checks if everything went fine
        {
            super.onPostExecute(result);

            if (!ConnectSuccess)
            {
                msg("Connection Failed. Is it a SPP Bluetooth? Try again.");
                finish();
            }
            else
            {
                msg("Connected.");
                isBtConnected = true;
            }
            progress.dismiss();
        }
    }
}

