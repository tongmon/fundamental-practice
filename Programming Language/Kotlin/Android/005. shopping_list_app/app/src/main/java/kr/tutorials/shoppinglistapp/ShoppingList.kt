package kr.tutorials.shoppinglistapp

import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.AlertDialog
import androidx.compose.material3.Button
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
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

    var itemName by remember {
        mutableStateOf("")
    }
    var itemQuantity by remember {
        mutableStateOf("")
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
                // 밑과 같이 추가된 아이템에 대한 컴포넌트를 적어주면 LazyColumn의 items가 내부적으로 반복문을 돌면서 추가된 컴포넌트를 화면에 뿌려준다.
                ShoppingListItem(it, {}, {})
            }
        }
    }

    if (showDialog) {
        AlertDialog(onDismissRequest = { showDialog = false },
            confirmButton = {
                Row(
                    modifier = Modifier
                        .fillMaxWidth()
                        .padding(8.dp),
                    horizontalArrangement = Arrangement.SpaceBetween
                ) {
                    Button(onClick = {
                        if (itemName.isNotBlank()) {
                            val newItem = ShoppingItem(
                                id = sItems.size + 1,
                                name = itemName,
                                quantity = itemQuantity.toInt()
                            )
                            // 상태 변수인 sItems를 변경함으로 해당 컴포넌트는 재렌더링 될 것이다.
                            sItems += newItem
                            showDialog = false
                            itemName = ""
                            itemQuantity = ""
                        }
                    }) {
                        Text(text = "Add")
                    }
                    Button(onClick = { showDialog = false }) {
                        Text(text = "Cancel")
                    }
                }
            },
            title = { Text(text = "Add Shopping Item") },
            // 인자는 text지만 내부적으로 모든 @Composable을 받을 수 있으니 밑과 같이 확장해서 사용할 수도 있다.
            text = {
                Column {
                    OutlinedTextField(
                        value = itemName,
                        // 여기서 it은 onValueChange의 String 인자를 의미하는데 이를 알 수 있는 방법은
                        // 'onValueChange = {'에서 '{' 부분에 마우스 커서를 올려보면 된다.
                        onValueChange = { itemName = it },
                        singleLine = true,
                        modifier = Modifier
                            .fillMaxWidth()
                            .padding(8.dp)
                    )
                    OutlinedTextField(
                        value = itemQuantity,
                        onValueChange = { itemQuantity = it },
                        singleLine = true,
                        modifier = Modifier
                            .fillMaxWidth()
                            .padding(8.dp)
                    )
                }
            })
    }
}

// LazyColumn에 추가할 컴포넌트를 정의한다.
// 컴포넌트에는 보통 이벤트 콜백이 들어가므로 인자에 함수 포인트를 넘겨주는 경우가 많은데
// 이 경우 `() -> Unit` 요런 식의 자료형을 이용하면 된다.
@Composable
fun ShoppingListItem(
    item: ShoppingItem,
    onEditClick: () -> Unit,
    onDeleteClick: () -> Unit
) {
    Row(
        modifier = Modifier
            .padding(8.dp)
            .fillMaxWidth()
            .border(
                border = BorderStroke(2.dp, Color(0xff018786)),
                shape = RoundedCornerShape(20)
            )
    ) {
        Text(text = item.name, modifier = Modifier.padding(8.dp))
    }
}