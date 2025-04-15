import { styled } from "styled-components";
import logo from "../assets/logo.png";

// styled-components에서 &를 사용하여 현재 선택된 nested 요소를 선택할 수 있다.
// 예를 들어 & img는 현재 선택된 요소의 img 태그를 선택하게 되고 이는 header img와 동일하다.
// @media 쿼리는 css의 if문이라고 보면 된다.
// 예를 들어 @media (min-width: 768px)는 화면의 가로 길이가 768px 이상일 때 적용되는 css를 작성할 수 있다.
const StyledHeader = styled.header`
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  margin-top: 2rem;
  margin-bottom: 2rem;

  & img {
    object-fit: contain;
    margin-bottom: 2rem;
    width: 11rem;
    height: 11rem;
  }

  & h1 {
    font-size: 1.5rem;
    font-weight: 600;
    letter-spacing: 0.4em;
    text-align: center;
    text-transform: uppercase;
    color: #9a3412;
    font-family: 'Pacifico', cursive;
    margin: 0;
  }

  & p {
    text-align: center;
    color: #a39191;
    margin: 0;
  }

  @media (min-width: 768px) {
    margin-bottom: 4rem;

    & h1 {
        font-size: 2.25rem;
    }
  }
`;

export default function Header() {
  return (
    <StyledHeader>
      <img src={logo} alt="A canvas" />
      <h1>ReactArt</h1>
      <p>
        A community of artists and art-lovers.
      </p>
    </StyledHeader>
  );
}
