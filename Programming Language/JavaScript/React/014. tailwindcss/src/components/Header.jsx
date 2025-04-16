import logo from '../assets/logo.png';

export default function Header() {
  return (
    // 이렇게 tailwind css를 사용하면, css를 따로 작성하지 않고도 스타일을 적용할 수 있다.
    // 다만 tailwind css 만의 규칙과 문법이 있기에 따로 학습이 필요하다.
    // 예를 들어 지금 mt-8은 margin-top: 2rem;의 의미이다.
    <header className="flex flex-col items-center mt-8 mb-16">
      <img src={logo} alt="A canvas" className='object-contain mb-8 w-44 h-44' />
      <h1 className='text-4xl font-semibold tracking-widest text-center uppercase text-amber-800 font-title'>ReactArt</h1>
      <p>A community of artists and art-lovers.</p>
    </header>
  );
}
