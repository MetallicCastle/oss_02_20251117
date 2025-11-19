# oss_02_20251117
오픈소스 SW개론 실습 테스트
※ 레파지토리 이름은 레파지토리가 생성된 날짜입니다.
* 레파지토리 주소: https://github.com/MetallicCastle/oss_02_20251117.git
---
# 과제2 11/19 - top, ps, jobs, kill에 대해서 조사하기
### 시작하기 앞서
top 명령어에 대해 조사하기 앞서서 무작정 블로그를 돌아다니는 것보단 한번쯤은 공신력 있는 자료에서 찾고싶은 명령어를 설명한 문서를 읽고 싶어서 곰곰히 생각해보았습니다. 
그 결과 man 명령어와 --help 명령어면 내용은 짧지만 이 기능을 개발한 개발자가 작성해둔 설명이므로 공신력이 있지 않을까 해서 한번 사용해보도록 하겠습니다.

```Shell
man top
```
위의 명령어를 작성했을때는 아래와 같은 결과를 출력합니다.
> This system has been minimized by removing packages and content that are
> not required on a system that users do not log into.
> 
> To restore this content, including manpages, you can run the 'unminimize'
> command. You will still need to ensure the 'man-db' package is installed.

번역을 해보자면
>이 시스템은 패키지 및 콘텐츠를 제거함으로써 최소화되었습니다.
사용자가 직접 로그인하지 않는 시스템에 필요하지 않습니다.
>
>이 콘텐츠를 복원하려면 'unminimize'를 실행할 수 있습니다.
명령어'Man-db' 패키지가 설치되어 있는지 확인해야 합니다.

아쉽게도 패키지가 최소화 되어있는 바람에 man 명령어를 통해 제가 원하는 기능에 대한 설명을 들으려면 man-db가 설치되어 있는 상태에서 unminimize 명령어를 사용해야합니다.
```Shell
sudo unminimize
```
를 치면 해결되지만 최소화된 컨테이너를 다시 원래 크기로 몸집을 불리는 행위이므로 함부로 치면 안되는 명령어 입니다.
저같은 경우엔 이 컨테이너에 중요한 작업물은 없어서 수틀리면 지우고 다시 생성하면 되므로 마음 편하게 입력하겠습니다.
sudo는 docker 컨테이너 환경이므로 생략해야합니다.

### top 명령어

설정완료후 다시 man top 명령어를 입력해 주었는데 매우 내용이 길어서 top_manual 파일에 리다이렉션을 통해 파일로 저장했습니다.
```Shell
man top > top_manual.txt
```

모든 내용은 레파지토리에 업로드 해두겠습니다.

일부인 Description 부분만 가져왔습니다.
```
DESCRIPTION
       The  top  program  provides  a  dynamic  real-time  view  of  a running system.  It can display system summary
       information as well as a list of processes or threads currently being managed by the Linux kernel.  The  types
       of  system  summary information shown and the types, order and size of information displayed for processes are
       all user configurable and that configuration can be made persistent across restarts.

       The program provides a limited interactive interface for process manipulation as well as a much more extensive
       interface  for  personal  configuration   --   encompassing  every  aspect of its operation.  And while top is
       referred to throughout this document, you are free to name the program anything  you  wish.   That  new  name,
       possibly  an  alias, will then be reflected on top's display and used when reading and writing a configuration
       file.
```

>top 프로그램은 실행중인 시스템의 동적 실시간 뷰를 제공합니다. 이 프로그램은 시스템 요약 정보 뿐만아니라, 현재 리눅스 커널이 관리하고 있는 프로세스나 스레드들의 목록을 표시할 수 있습니다.
>표시되는 시스템 요약 정보의 종류나 프로세스 정보의 종류, 순서, 크기는 모두 사용자가 설정할 수 있으며, 이 설정은 프로그램을 재시작해도 유지되도록 저장할 수 있습니다.

>이 프로그램은 프로세스를 조작(제어)하기위한 제한된 대화영 인터페이스를 제공하며, 작동의 모든 측면을 아우르는 훨씬 더 광범위한 개인 설정 인터페이스도 제공합니다.
>이 문서 전반에 걸쳐 top이라고 지칭하고 있지만, 여러분은 이 프로그램의 이름을 원하는대로 자유롭게 지정할 수 있습니다. 그 새로운 이름(또는 별칭)은 top 화면 상단에 표시되며, 설정 파일을 읽거나 쓸 때도 사용됩니다.

간단히 요약하자면 윈도우시스템의 **작업관리자**같이 컴퓨팅 자원 사용량과 **실행중인 프로그램을 실시간으로 모니터링**을 하며, **프로세스를 강제종료**시키거나 **우선순위를 변경**할 수 있다고 합니다.
또한 자신만만하게 화면에 표시되는 정보를 입맛대로 수정할 수 있다고 당당하게 내세우는 모습을 보아 리눅스의 오픈소스적인 특징을 잘 나타내는 것 같습니다.


