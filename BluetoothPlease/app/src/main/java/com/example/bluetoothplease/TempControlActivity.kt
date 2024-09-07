/*
package com.example.bluetoothplease

import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.activity.ComponentActivity
//import androidx.compose.ui.tooling.data.EmptyGroup.data

class TempControlActivity : ComponentActivity() {

    private lateinit var editTextTemperature: EditText
    private lateinit var buttonSubmitTemp: Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_temp_control)

        editTextTemperature = findViewById(R.id.editTextTemperature)
        buttonSubmitTemp = findViewById(R.id.buttonSubmitTemp)

        buttonSubmitTemp.setOnClickListener {
            val temperature = editTextTemperature.text.toString()
            if (temperature.isNotEmpty()) {
                sendTemperatureToArduino(temperature)
                Toast.makeText(this, "Temperature sent: $temperature", Toast.LENGTH_SHORT).show()
            } else {
                Toast.makeText(this, "Please enter a valid temperature", Toast.LENGTH_SHORT).show()
            }
        }
    }

    private fun sendTemperatureToArduino(temperature: String) {
        // Send the temperature data via Bluetooth to Arduino
        val command = "T$temperature"  // Example: send as "T24"
        //(applicationContext as MainActivity).connectedThread?.write(command)
        MainActivity.connectedThread?.write(command)

    }
}
*/
package com.example.bluetoothplease

import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.activity.ComponentActivity

class TempControlActivity : ComponentActivity() {

    private lateinit var editTextTemperature: EditText
    private lateinit var buttonSubmitTemp: Button

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_temp_control)

        // UI 요소 연결
        editTextTemperature = findViewById(R.id.editTextTemperature)
        buttonSubmitTemp = findViewById(R.id.buttonSubmitTemp)

        // 버튼 클릭 시 온도 전송
        buttonSubmitTemp.setOnClickListener {
            val temperature = editTextTemperature.text.toString()

            if (temperature.isNotEmpty()) {
                sendTemperatureToArduino(temperature)
            } else {
                Toast.makeText(this, "Please enter a valid temperature", Toast.LENGTH_SHORT).show()
            }
        }
    }

    // 아두이노로 온도 데이터를 전송하는 함수
    private fun sendTemperatureToArduino(temperature: String) {
        // Bluetooth로 보낼 명령어 형식 (예: "T24")
        val command = "T$temperature"

        // connectedThread가 null이 아닌지 확인하고 데이터 전송
        if (MainActivity.connectedThread != null) {
            MainActivity.connectedThread?.write(command)
            Toast.makeText(this, "Temperature sent: $temperature", Toast.LENGTH_SHORT).show()
        } else {
            Toast.makeText(this, "Bluetooth connection is not established", Toast.LENGTH_SHORT).show()
        }
    }
}
