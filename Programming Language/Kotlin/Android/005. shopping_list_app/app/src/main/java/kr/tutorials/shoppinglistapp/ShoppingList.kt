package kr.tutorials.shoppinglistapp

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.Dp
import androidx.compose.ui.unit.dp

data class ShoppingItem(
    val id: Int,
    var name: String,
    var quantity: Int,
    var isEditing: Boolean = false
)

@Composable
fun ShoppingListApp(innerPadding: PaddingValues) {
    var sItems by remember { mutableStateOf(listOf<ShoppingItem>()) }

    // 상태 변수이기에 해당 변수가 변경될 때마다 ShoppingListApp() 컴포넌트는 재렌더링된다.
    var showDialog by remember {
        mutableStateOf(false)
    }

    Column(
        modifier = Modifier
            .padding(innerPadding)
            .fillMaxSize(),
        verticalArrangement = Arrangement.Center
    ) {
        Button(
            onClick = { showDialog = true },
            modifier = Modifier.align(Alignment.CenterHorizontally)
        ) {
            Text("Add Item")
        }
        // LazyColumn은 동적 배열 UI를 만들 때 사용된다.
        // 예를 들어 인스타 그램 페이지를 밑으로 무한정 내릴 수 있는 그런 상황에서 사용될 수 있다.
        LazyColumn(
            modifier = Modifier
                .fillMaxSize()
                .padding(16.dp)
        ) {
            // 해당 LazyColumn과 연동되는 상태 변수 아이템 묶음은 밑과 같이 연결할 수 있다.
            items(sItems) {

            }
        }
    }

    if (showDialog) {
        AlertDialog(onDismissRequest = { showDialog = false },
            confirmButton = { /*TODO*/ },
            text = { Text("I am an alert dialog!") })
    }
}