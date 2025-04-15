import { styled } from 'styled-components';

// hover인 경우는 &:hover로 작성할 수 있다.
// &는 현재 선택자를 의미하기에 &:hover는 button:hover와 동일하다.
export const Button = styled.button`
  padding: 1rem 2rem;
  font-weight: 600;
  text-transform: uppercase;
  border-radius: 0.25rem;
  color: #1f2937;
  background-color: #f0b322;
  border-radius: 6px;
  border: none;

  &:hover {
    background-color: #f0920e;
  }
`;