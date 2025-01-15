// ...props를 이용하여 사용자 지정 prop이였던 onSelect를 제거하여 중간 다리가 없어져 더 간결해졌다.
// 이제 TabButton에 직접 html에서 제공하는 onClick을 지정할 수 있게 되었다.
export function TabButton({ children, isSelected, ...props }) {
  console.log("TABBUTTON COMPONENT EXECUTING");
  return (
    <li>
      <button className={isSelected ? "active" : undefined} {...props}>
        {children}
      </button>
    </li>
  );
}
