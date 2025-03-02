package kr.tutorials.unitconverter

import android.os.Bundle
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.material3.Icon
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.width
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowDropDown
import androidx.compose.material3.Button
import androidx.compose.material3.DropdownMenu
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Scaffold
import androidx.compose.material3.SegmentedButtonDefaults.Icon
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableDoubleStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.unit.dp
import androidx.compose.ui.Modifier
import androidx.compose.ui.modifier.modifierLocalConsumer
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.tooling.preview.Preview
import kr.tutorials.unitconverter.ui.theme.UnitConverterTheme
import kotlin.math.roundToInt

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            UnitConverterTheme {
                // Scaffold라는 UI를 화면에 가득 채우기위해 Modifier.fillMaxSize()를 전달함
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    UnitConverter(Modifier.padding(innerPadding))
                }
            }
        }
    }
}

@Composable
fun UnitConverter(modifier: Modifier = Modifier) {

    var inputValue by remember {
        mutableStateOf("")
    }
    var outputValue by remember {
        mutableStateOf("")
    }
    var inputUnit by remember {
        mutableStateOf("")
    }
    var outputUnity by remember {
        mutableStateOf("")
    }
    var iExpanded by remember {
        mutableStateOf(false)
    }
    var oExpanded by remember {
        mutableStateOf(false)
    }
    val conversionFactor = remember {
        mutableDoubleStateOf(0.01)
    }

    fun convertUnits() {
        // 밑 라인은 많은 기능을 함축하고 있다.
        // toDoubleOrNull() 함수는 inputValue 문자열 변수가 double 형으로 변환이 가능한 녀석이면 double 값을 반환하고
        // 그것이 불하는 하면 null을 반환하는데 '?:' syntex로 인해 null인 경우 0.0이 선택되어
        // 결과적으로 inputValue 값이 double형으로 변환가능하면 해당 값을, 아니라면 0.0을 반환하는 로직이라고 볼 수 있다.
        val inputValueDouble = inputValue.toDoubleOrNull() ?: 0.0

        val result =
            (inputValueDouble * (1 / conversionFactor.doubleValue) * 100.0).roundToInt() / 100.0
        outputValue = result.toString()
    }

    // Column에 여러 인자들을 넣어 내부 정렬, 크기 등을 조절할 수 있다.
    // Modifier는 Modifier.fillMaxSize().padding()과 같이 빌더 패턴으로 확장이 유연하다.
    Column(
        modifier = modifier.fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        // modifier = Modifier.padding(100.dp) 코드를 사용해도 UI 간격 조절이 가능하다.
        Text(text = "Unit Converter" /*, modifier = Modifier.padding(100.dp)*/)
        // Spacer를 통해 UI간 간격을 조절할 수 있음
        // dp는 화면 상대적인 단위라 화면 크기 제약이 없어서 좋다.
        Spacer(modifier = Modifier.height(16.dp))
        // Text Field에 문자가 입력될 때마다 상태 변수 값을 변경하고
        // 해당 값을 다시 Text Field에 할당하여 Text Field 값이 inputValue에 실시간으로 반영되도록 해준다.
        OutlinedTextField(value = inputValue,
            onValueChange = {
                inputValue = it
            },
            label = { Text("Enter Value") })
        Spacer(modifier = Modifier.height(16.dp))
        Row {
            // 복잡한 레이아웃을 설계할 때 Box가 사용된다.
            // Box안에 같이 Button과 DropdownMenu를 위치시킴으로 두 UI가 같은 context를 공유하게 되고 상호작용이 가능하다.
            Box {
                Button(onClick = { iExpanded = true }) {
                    Text(text = "Select")
                    Icon(
                        Icons.Default.ArrowDropDown,
                        contentDescription = "Arrow Down"
                    )
                }
                // onDismissRequest는 드롭박스 메뉴를 닫으려는 메시지가 전달되는 경우 트리거 된다.
                DropdownMenu(expanded = iExpanded, onDismissRequest = { iExpanded = false }) {
                    DropdownMenuItem(
                        text = { Text(text = "Millimeters") },
                        onClick = {
                            iExpanded = false
                            inputUnit = "Millimeters"
                            conversionFactor.doubleValue = 0.001
                            convertUnits()
                        }
                    )
                    DropdownMenuItem(
                        text = { Text(text = "Centimeters") },
                        onClick = {
                            iExpanded = false
                            inputUnit = "Centimeters"
                            conversionFactor.doubleValue = 0.01
                            convertUnits()
                        }
                    )
                    DropdownMenuItem(
                        text = { Text(text = "Meters") },
                        onClick = {
                            iExpanded = false
                            inputUnit = "Centimeters"
                            conversionFactor.doubleValue = 1.0
                            convertUnits()
                        }
                    )
                    DropdownMenuItem(
                        text = { Text(text = "Feet") },
                        onClick = {
                            iExpanded = false
                            inputUnit = "Feet"
                            conversionFactor.doubleValue = 0.3048
                            convertUnits()
                        }
                    )
                }
            }
            Spacer(modifier = Modifier.width(16.dp))
            Box {
                Button(onClick = { oExpanded = true }) {
                    Text(text = "Select")
                    Icon(
                        Icons.Default.ArrowDropDown,
                        contentDescription = "Arrow Down"
                    )
                }
                DropdownMenu(expanded = oExpanded, onDismissRequest = { oExpanded = false }) {
                    DropdownMenuItem(
                        text = { Text(text = "Millimeters") },
                        onClick = { }
                    )
                    DropdownMenuItem(
                        text = { Text(text = "Centimeters") },
                        onClick = { }
                    )
                    DropdownMenuItem(
                        text = { Text(text = "Meters") },
                        onClick = { }
                    )
                    DropdownMenuItem(
                        text = { Text(text = "Feet") },
                        onClick = { }
                    )
                }
            }
        }
        Spacer(modifier = Modifier.height(16.dp))
        Text("Result: $outputValue")
    }

    // Column(modifier = modifier) {
    //     Text(text = "Unit Converter")
    //     OutlinedTextField(value = "", onValueChange = {
    //         // Text Field 내부 텍스트가 변할 때마다 호출되는 Callback 함수
    //     })
    //     Row {
    //         // Android에서 context란 어플리케이션에서 현재 상태를 나타내거나 알아내는 경우 사용된다.
    //         val context = LocalContext.current
    //         // Toast는 특정 시간 후에 사라지는 간단한 팝업 메시지 UI라고 생각하면 된다.
    //         Button(onClick = { Toast.makeText(context, "Thanks for clicking!", Toast.LENGTH_LONG).show() }) {
    //             Text(text = "Click Me!")
    //         }
    //     }
    //     Text(text = "Result:")
    // }
}

// 모든 UI를 위한 함수에는 밑과 같이 @Composable이라는 annotation이 있어야 한다.
// 이렇게 해야 @Composable에서 지원하는 UI 관련 라이브러리들을 함수 내에서 사용할 수 있다.
@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    // 글자 UI
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview
@Composable
fun UnitConverterPreview() {
    UnitConverter()
}


@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    UnitConverterTheme {
        Greeting("Android")
    }
}