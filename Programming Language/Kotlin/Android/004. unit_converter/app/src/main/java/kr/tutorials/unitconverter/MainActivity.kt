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
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowDropDown
import androidx.compose.material3.Button
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Scaffold
import androidx.compose.material3.SegmentedButtonDefaults.Icon
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.modifier.modifierLocalConsumer
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.tooling.preview.Preview
import kr.tutorials.unitconverter.ui.theme.UnitConverterTheme

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
    // Column에 여러 인자들을 넣어 내부 정렬, 크기 등을 조절할 수 있다.
    // Modifier는 Modifier.fillMaxSize().padding()과 같이 빌더 패턴으로 확장이 유연하다.
    Column(
        modifier = modifier.fillMaxSize(),
        verticalArrangement = Arrangement.Center,
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(text = "Unit Converter")
        OutlinedTextField(value = "", onValueChange = {
        })
        Row {
            // 복잡한 레이아웃을 설계할 때 Box가 사용된다.
            Box {
                Button(onClick = { /*TODO*/ }) {
                    Text(text = "Select")
                    Icon(
                        Icons.Default.ArrowDropDown,
                        contentDescription = "Arrow Down"
                    )
                }
            }
            Box {
                Button(onClick = { /*TODO*/ }) {
                    Text(text = "Select")
                    Icon(
                        Icons.Default.ArrowDropDown,
                        contentDescription = "Arrow Down"
                    )
                }
            }
        }
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