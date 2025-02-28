package kr.tutorials.myapplication

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import kr.tutorials.myapplication.ui.theme.MyApplicationTheme
import kotlin.random.Random

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            MyApplicationTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    CaptainGame(Modifier.padding(innerPadding))
                }
            }
        }
    }

    @Composable
    fun CaptainGame(modifier: Modifier) {
        // 상태 변수 선언은 밑과 같이 remember를 사용해야 한다.
        // 상태 변수가 일반 변수랑 다른 점은 해당 변수가 변경이 되는 경우 UI랑 바인딩이 되어 있기에
        // 해당 변수에 묶인 UI를 코틀린이 알아서 재렌더링을 해준다는 것이다.
        val treasuresFound = remember { mutableIntStateOf(0) }
        val direction = remember {
            mutableStateOf("North")
        }

        Column(
            modifier = modifier.fillMaxSize(),
            verticalArrangement = Arrangement.Center,
            horizontalAlignment = Alignment.CenterHorizontally
        ) {
            // 상태 변수에 접근하려면 value(혹은 자료형에 따라 요구되는 멤버 변수)를 추가적으로 호출해줘야 함
            Text("Treasure Found: ${treasuresFound.intValue}")
            Text("Current Direction: ${direction.value}")
            Button(onClick = {
                // 상태 변수는 단지 밑과 같이 수정하면 된다.
                direction.value = "East"
                if (Random.nextBoolean()) {
                    treasuresFound.intValue += 1
                }
            }) {
                Text("Sail East")
            }
            Button(onClick = {
                direction.value = "West"
                if (Random.nextBoolean()) {
                    treasuresFound.intValue += 1
                }
            }) {
                Text("Sail West")
            }
            Button(onClick = {
                direction.value = "North"
                if (Random.nextBoolean()) {
                    treasuresFound.intValue += 1
                }
            }) {
                Text("Sail North")
            }
            Button(onClick = {
                direction.value = "South"
                if (Random.nextBoolean()) {
                    treasuresFound.intValue += 1
                }
            }) {
                Text("Sail South")
            }
        }
    }
}

