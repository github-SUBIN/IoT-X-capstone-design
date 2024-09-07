package com.example.bluetoothplease

import android.os.Bundle
import android.widget.Button
import androidx.activity.ComponentActivity


class WindowControlActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_window_control)

        val button0: Button = findViewById(R.id.button0)
        val button20: Button = findViewById(R.id.button20)
        val button40: Button = findViewById(R.id.button40)
        val button60: Button = findViewById(R.id.button60)
        val button80: Button = findViewById(R.id.button80)
        val button100: Button = findViewById(R.id.button100)

        // Set click listeners for each button
        val transparencyButtons = listOf(button0, button20, button40, button60, button80, button100)
        transparencyButtons.forEach { button ->
            button.setOnClickListener {
                val transparencyValue = button.text.toString().replace("%", "") // % 제거
                val message = "W$transparencyValue" // W 명령어와 함께 전송
                MainActivity.connectedThread?.write(message) // Send via Bluetooth
            }

            /*
            button.setOnClickListener {
                val transparencyValue = button.text.toString() // Get the percentage text (e.g., "0%")
                MainActivity.connectedThread?.write(transparencyValue) // Send via Bluetooth
            }
            */
        }
    }
}
