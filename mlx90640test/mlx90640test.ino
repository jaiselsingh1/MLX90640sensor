// Include the library for the MLX90640 thermal camera
#include <Adafruit_MLX90640.h>

// Create an instance of the MLX90640 sensor
Adafruit_MLX90640 mlx;

// The MLX90640 sensor has a resolution of 32x24 pixels (768 total pixels)
// Create an array to store all temperature readings
float frame[32*24];

void setup() {
  // Start serial communication at 115200 baud rate
  Serial.begin(115200);
  delay(1000);  // Wait a second for serial to be ready
  
  Serial.println("Starting MLX90640 Test...");
  
  // Initialize I2C communication
  Wire.begin();
  // Set I2C clock to 100kHz for reliable communication
  Wire.setClock(100000);
  
  // Try to connect to the MLX90640 sensor
  if (!mlx.begin(MLX90640_I2CADDR_DEFAULT, &Wire)) {// the CADDR default refers to the default memory address that's given to the mlx sensor 
    Serial.println("Could not find the MLX90640 sensor!");
    Serial.println("Check your wiring.");
    while (1) delay(10);
  }
  
  Serial.println("MLX90640 sensor found!");
  
  // Configure sensor settings:
  // CHESS mode alternates readings to reduce thermal leakage between pixels
  mlx.setMode(MLX90640_CHESS);
  
  // Set resolution to 18 bits for better accuracy
  // Options are: 16 bit (faster) to 18 bit (more precise)
  mlx.setResolution(MLX90640_ADC_18BIT);
  
  // Set refresh rate to 2Hz (2 frames per second)
  mlx.setRefreshRate(MLX90640_2_HZ);
  
  Serial.println("Setup complete!");
}

void loop() {
  Serial.println("\nReading temperatures...");
  
  // Try to get a frame of temperature data
  if (mlx.getFrame(frame) != 0) {
    Serial.println("Failed to read from sensor!");
    delay(500);
    return;
  }
  
  // Print temperatures from a 3x3 grid in the center of the sensor
  // This is easier to read than all 768 pixels
  Serial.println("\nCenter 3x3 temperatures (°C):");
  
  // Calculate center positions
  int centerRow = 12;  // Center row (24/2)
  int centerCol = 16;  // Center column (32/2)
  
  // Print 3x3 grid
  for (int row = centerRow-1; row <= centerRow+1; row++) {
    for (int col = centerCol-1; col <= centerCol+1; col++) {
      // Calculate position in the frame array
      int position = row * 32 + col;
      // Get temperature at this position
      float temperature = frame[position];
      // Print temperature with 1 decimal place
      Serial.print(temperature, 1);
      Serial.print("°C\t");
    }
    Serial.println();  // New line after each row
  }
  
  // Find minimum and maximum temperatures from all pixels
  float maxTemp = -273.15;  // Start with absolute zero
  float minTemp = 1000;     // Start with a very high number
  
  for (int pixel = 0; pixel < 32*24; pixel++) {
    float temp = frame[pixel];
    // Update maximum temperature if we find a higher one
    if (temp > maxTemp) maxTemp = temp;
    // Update minimum temperature if we find a lower one
    // Ignore clearly invalid readings below absolute zero
    if (temp < minTemp && temp > -273.15) minTemp = temp;
  }
  
  // Print the min and max temperatures
  Serial.print("\nHottest temperature: ");
  Serial.print(maxTemp, 1);
  Serial.println("°C");
  
  Serial.print("Coldest temperature: ");
  Serial.print(minTemp, 1);
  Serial.println("°C");
  
  // Wait half a second before next reading
  delay(500);
}
