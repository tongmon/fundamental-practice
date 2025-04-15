import { styled } from 'styled-components';

// styled-components는 color 속성을 보면 알겠지만 함수를 사용하여 props를 전달받을 수 있다.
// 함수를 전달할 때 ({ $invalid }) => ($invalid ? '#f87171' : '#6b7280') 이런 형식을 사용한 다는 것을 기억하자.
// 위 형식에서 (), {}가 생략되면 제대로 동작하지 않는다.
const Label = styled.label`
  display: block;
  margin-bottom: 0.5rem;
  font-size: 0.75rem;
  font-weight: 700;
  letter-spacing: 0.1em;
  text-transform: uppercase;
  color: ${({ $invalid }) => ($invalid ? '#f87171' : '#6b7280')};
`;

const Input = styled.input`
  width: 100%;
  padding: 0.75rem 1rem;
  line-height: 1.5;
  background-color: ${({ $invalid }) => ($invalid ? '#fed2d2' : '#d1d5db')};
  color: ${({ $invalid }) => ($invalid ? '#ef4444' : '#374151')};
  border: 1px solid transparent;
  border-radius: 0.25rem;
  border - color: ${({ $invalid }) => ($invalid ? '#f73f3f' : 'transparent')};
  box-shadow: 0 1px 3px 0 rgba(0, 0, 0, 0.1), 0 1px 2px 0 rgba(0, 0, 0, 0.06);
`;

// Label과 Input을 모두 export하기 보다는 이 둘을 합쳐서 CustomInput 컴포넌트만 export하는 편이 더 깔끔하다.
// 항상 재사용성을 고려하자.
export function CustomInput({ children, invalid, ...props }) {
  return (
    // label 태그도 마찬가지로 위에서 정의한 styled.label로 바꿔주면 된다.
    // styled-components에서 invalid와 같이 props로 값을 전달하여 동적 스타일링을 구현 할 수 있다.
    // styled-components의 props는 내장 프로퍼티의 이름과 충돌을 피하기 위해 $로 시작하는 것이 좋다.
    <p>
      <Label $invalid={invalid}>{children}</Label>
      <Input $invalid={invalid} {...props} />
    </p>
  )
}

