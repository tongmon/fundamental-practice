// 밑과 같이 사용자 정의 섹션을 만들어서 사용할 수 있다.
// 주의할 점은 기존의 html에서 제공되는 <section> 태그에서는 <sestion id="examples">와 같이 id를 지정할 수 있지만
// 사용자 정의 컴포넌트는 따로 id에 대한 props를 지정해주지 않으면 <Section id="examples">와 같이 사용해도 아무일도 발생하지 않는다.
// 즉 magic connection이 없다는 것이다.
// 이러한 magic connection을 만들어주는 방법이 있는데 바로 `...props`를 사용하는 것이다.
// 밑과 같이 `...props`를 통해 title과 같이 개별적으로 지정해야 하는 속성을 제외하면 모두 props로 묶여 전달된다.
export function Section({ title, children, ...props }) {
  return (
    <section {...props}>
      <h2>{title}</h2>
      {children}
    </section>
  );
}
