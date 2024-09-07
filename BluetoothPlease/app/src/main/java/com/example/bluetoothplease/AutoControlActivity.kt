package com.example.bluetoothplease

import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.Toast
import androidx.activity.ComponentActivity

class AutoControlActivity : ComponentActivity() {

    //private lateinit var autoStart: Button
    //private lateinit var autoEnd: Button

    override fun onCreate(savedInstanceState: Bundle?) {
        //Log.d("AutoControlActivity", "Activity started")

        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_auto_control)


        //UI 요소 연결
        val autoStart: Button = findViewById(R.id.autoStart)
        val autoEnd: Button = findViewById(R.id.autoEnd)

        //버튼 클릭 시 아두이노로 시작 명령어S 전송
        autoStart.setOnClickListener {
            sendSignalToArduino("S1")

        }

        //버튼 클릭 시 아두이노로 끝 명령어E 전송
        autoEnd.setOnClickListener {
            sendSignalToArduino("E0")

        }
    }
    //아두이노로 자동 시작, 자동 끝 명령어를 전송하는 함수
    private fun sendSignalToArduino(message: String){
        MainActivity.connectedThread?.write(message)
        /*
        MainActivity.connectedThread?.let {
            it.write(message)
        } ?: run {
            Log.e("AutoControlActivity", "Bluetooth is not connected.")
        }
        */
        /*
        if(MainActivity.connectedThread != null){
            MainActivity.connectedThread?.write(message)
            Toast.makeText(this,"AutoStart sent: $message", Toast.LENGTH_SHORT).show()
        } else {
            Toast.makeText(this,"Bluetooth connection is not established", Toast.LENGTH_SHORT).show()
            Log.e("AutoControlActivity", "Bluetooth connection not established.")
        }
        */
    }
}