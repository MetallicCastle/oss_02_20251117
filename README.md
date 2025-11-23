# oss_02_20251117
오픈소스 SW개론 실습 테스트
※ 레파지토리 이름은 레파지토리가 생성된 날짜입니다.
* 레파지토리 주소: <https://github.com/MetallicCastle/oss_02_20251117.git>

---

# 과제2 11/19 - top, ps, jobs, kill에 대해서 조사하기
### 시작하기 앞서
top 명령어에 대해 조사하기 앞서서 무작정 웹이나 블로그 내용만 넣는 것보단 한번쯤은 공신력 있는 자료에서 찾고싶은 명령어를 설명한 문서를 읽고 싶어서 곰곰히 생각해보았습니다. 
그 결과 man 명령어와 --help 명령어면 내용은 이 기능을 개발한 개발자가 작성해둔 설명이므로 공신력이 있지 않을까 해서 한번 사용해보도록 하겠습니다.

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
를 치면 해결되지만 최소화된 컨테이너를 다시 원래 크기로 몸집을 불리는 행위이므로 **함부로 치면 안되는 명령어** 입니다.
저같은 경우엔 이 컨테이너에 중요한 작업물은 없어서 수틀리면 지우고 다시 생성하면 되므로 마음 편하게 입력하겠습니다.
sudo는 docker 컨테이너 환경이므로 생략해야합니다.

---

---

## top 명령어

설정완료후 다시 man top 명령어를 입력해 주었는데 매우 내용이 길어서 top_manual 파일에 리다이렉션을 통해 파일로 저장했습니다.
```Shell
man top > top_manual.txt
```

모든 내용은 레파지토리에 업로드 해두겠습니다.

일부인 Description 부분만 가져왔습니다.
>```
>DESCRIPTION
>       The  top  program  provides  a  dynamic  real-time  view  of  a running system.  It can display system summary
>       information as well as a list of processes or threads currently being managed by the Linux kernel.  The  types
>       of  system  summary information shown and the types, order and size of information displayed for processes are
>       all user configurable and that configuration can be made persistent across restarts.
>
>       The program provides a limited interactive interface for process manipulation as well as a much more extensive
>       interface  for  personal  configuration   --   encompassing  every  aspect of its operation.  And while top is
>       referred to throughout this document, you are free to name the program anything  you  wish.   That  new  name,
>       possibly  an  alias, will then be reflected on top's display and used when reading and writing a configuration
>       file.
>```

>top 프로그램은 실행중인 시스템의 동적 실시간 뷰를 제공합니다. 이 프로그램은 시스템 요약 정보 뿐만아니라, 현재 리눅스 커널이 관리하고 있는 프로세스나 스레드들의 목록을 표시할 수 있습니다.
>표시되는 시스템 요약 정보의 종류나 프로세스 정보의 종류, 순서, 크기는 모두 사용자가 설정할 수 있으며, 이 설정은 프로그램을 재시작해도 유지되도록 저장할 수 있습니다.
>
>이 프로그램은 프로세스를 조작(제어)하기위한 제한된 대화영 인터페이스를 제공하며, 작동의 모든 측면을 아우르는 훨씬 더 광범위한 개인 설정 인터페이스도 제공합니다.
>이 문서 전반에 걸쳐 top이라고 지칭하고 있지만, 여러분은 이 프로그램의 이름을 원하는대로 자유롭게 지정할 수 있습니다. 그 새로운 이름(또는 별칭)은 top 화면 상단에 표시되며, 설정 파일을 읽거나 쓸 때도 사용됩니다.

간단히 요약하자면 윈도우시스템의 **작업관리자**같이 **컴퓨팅 자원 사용량**과 **실행중인 프로그램을 실시간으로 모니터링**을 하며, **프로세스를 강제종료**시키거나 **우선순위를 변경**할 수 있다고 합니다.
또한 자신만만하게 화면에 표시되는 정보를 입맛대로 수정할 수 있다고 당당하게 내세우는 모습을 보아 리눅스의 오픈소스적인 특징을 잘 나타내는 것 같습니다.

---

#### 표시되는 정보 구성
<img width="1226" height="419" alt="image" src="https://github.com/user-attachments/assets/0ba34354-883b-4a8b-8514-97a997b4f224" />

실행시 위와같은 정보가 표시되며, `vim` 이나 `tail -f` 명령어같이 다음 명령어 입력상태가 아닌 명령이 계속 실행된 상태로 유지됩니다.

내용은 크게 상단부분과 하단부분으로 나뉘어 있습니다.

---

##### 요약 영역 - 컴퓨터 자원 사용량
상단부분은 요약 영역이라 불리며 아래와 같은 구조로 이루어져 있습니다.

* 첫번째 줄에는 현재시간, OS가 살아있는 시간, 접속중인 유저수, 평균 부하 정보가 표시되어있고 평균부하는 앞에서부터 1분, 5분, 15분을 기준으로한 평균값입니다.
* 두번째 줄에는 작업중인 프로세스 개수를 표시하는데 아래와 같습니다.
  * <총 프로세스>
  * <실행중인 프로세스>
  * <대기중인 프로세스>
  * <종료된 프로세스>
  * <좀비 프로세스?>
* 세번째줄은 cpu부하이며 각각 아래의 의미를 갖습니다.
  * <us : 유저영역>
  * <sy : 커널영역>
  * <ni : 우선순위 설정>
  * <id : 여유공간>
  * <wa : IO 인터럽트 대기중>
  * <hi : 하드웨어 인터럽트 대기>
  * <si : 소프트웨어 인터럽트 대기>
  * <st : vm에서 사용할때 대기>
* 네번째~다섯번째줄은 메모리 부하상태를 확인할 수 있습니다.

cpu 부하에서 유저영역, 커널영역에 걸린 부하를 분리할 수는 있어도 각종 인터럽트에 심지어 가상머신상태일때 cpu사용권 대기할때 부하까지 표시하는 것을 보고 꽤나 세부적으로 표시한다는 생각이 들었습니다.

좀비프로세스는 프로세스가 종료되고 자원을 반납하고 종료되는 과정에서 부모 프로세스가 종료를 불가피한 상황에서 승인하지 못하는 경우에 발생한다고 합니다.
자원은 반납되어서 성능에 큰 악영향을 미치는 것은 아니지만 pid를 낭비한다는 점에서 좋은 상황은 아닙니다.

메모리가 2줄로 나누어져있는데, 네번째 줄에 있던 메모리 정보는 일반 메모리 사용량이고, swamp 메모리 사용량은 가상메모리처럼 일반 메모리가 가득 찼을경우 물리디스크에 저장되는 메모리의 양입니다.

---

##### 디테일 영역 - 실행중인 프로그램 실시간 모니터링
* PID
  * PID는 프로세스에게 부여되는 고유한 값입니다. kill 명령어를 입력할때 사용됩니다.
* USER
  * 해당 프로세스를 실행하거나 영향을 받는 사용자를 표시합니다.
* PR & NI
  * PR : 커널에 의해 스케쥴링될때의 우선순위 입니다.
  * NI : PR에 영향을 주는 nice라는 수치라고 합니다.
* VIRT, RES, SHR, %MEM
  * 위 네 속성은 메모리와 괸련된 필드입니다.
  * VIRT : 프로세스가 점유하는 총 메모리입니다.
  * RES : RAM에서 사용중인 메모리 크기입니다.
  * SHR : 다른 프로세스와 공유하는 공유메모리상용량입니다.
  * %MEM : 총 RAM에서 RES가 사용되는 비율입니다.
* S : 프로세스의 현재 상태를 의미합니다.
> ```
> 29. S  --  Process Status
>           The status of the task which can be one of:
>               D = uninterruptible sleep
>               I = idle
>               R = running
>               S = sleeping
>               T = stopped by job control signal
>               t = stopped by debugger during trace
>               Z = zombie
>
>           Tasks shown as running should be more properly thought of as ready to run  --  their task_struct is simply
>           represented on the Linux run-queue.  Even without a true SMP machine, you may see numerous tasks  in  this
>           state depending on top's delay interval and nice value.
>  ```
  * `D`는 간섭이 불가한 sleep상태
  * `I`는 아무것도 하지 않는 유휴상태
  * `R`은 싱행중 상태
  * `S`는 요청이 올때까지 대기중인 sleep 상태
  * `T`는 사용자에 의해 일시정지된 상태
  * `t`는 디버거등에 의해 일시정지된 상태
  * `Z`는 좀비상태
* TIME+
  * 프로세스가 사용한 총 CPU 시간
* COMMAND
   * 해당 프로세스를 실행한 커맨드

---

##### 프로세스를 강제로 종료하는 내부 명령어
>```
>       *  k  :Kill-a-task
>              You will be prompted for a PID and then the signal to send.
>
>              Entering no PID or a negative number will be interpreted as the default shown in the prompt (the  first
>              task displayed).  A PID value of zero means the top program itself.
>
>              The  default  signal,  as  reflected  in the prompt, is SIGTERM.  However, you can send any signal, via
>              number or name.
>
>              If you wish to abort the kill process, do one of the following depending on your progress:
>                  1) at the pid prompt, type an invalid number
>                  2) at the signal prompt, type 0 (or any invalid signal)
>                  3) at any prompt, type <Esc>
>```
top 화면 내에서 k를 입력하면 프로세스를 중단시킬 수 있습니다.

마침 이전의 이미지속 디테일 영역에 실행중인 top프로세스가 있었으니 종료시켜 보도록 하겠습니다.

<img width="759" height="228" alt="image" src="https://github.com/user-attachments/assets/308cc4c9-0ad8-4b6b-886e-285741105e88" />

k키를 입력하니 이 부분이 추가된 모습을 볼 수 있습니다.

화면에 표시된 pid `7932` 를 입력해보겠습니다.

<img width="762" height="230" alt="image" src="https://github.com/user-attachments/assets/4b42ab14-2e6f-406a-b88a-8743329bd69b" />

<img width="771" height="191" alt="image" src="https://github.com/user-attachments/assets/30fefcdf-22ec-4af1-9f66-ffc9541fdec8" />

enter을 누르니 종료되는 모습을 볼 수 있습니다. 

<img width="1074" height="365" alt="image" src="https://github.com/user-attachments/assets/fe036c0e-3bcc-4751-8499-76831796b0bb" />

종료되어서 맨 아래에 명령어 입력하는 공간이 `root@687046470c4a:/tmp#`이와 같이 떴습니다.
(※ kill하면 바로 명령어 입력창이 뜨는게 아니라 enter을 눌러야 종료된것에 반응하는지 몰랐어서 다시 재현했습니다. 이때는 pid가 7934이고 7934를 입력한것이 맞습니다.)

---

##### 프로세스의 우선순위를 변경하는 방법
>```
> *  r  :Renice-a-Task
>              You will be prompted for a PID and then the value to nice it to.
>
>              Entering no PID or a negative number will be interpreted as the default shown in the prompt (the  first
>              task displayed).  A PID value of zero means the top program itself.
>
>              A  positive  nice  value will cause a process to lose priority.  Conversely, a negative nice value will
>              cause a process to be viewed more favorably by the kernel.  As a general rule, ordinary users can  only
>              increase the nice value and are prevented from lowering it.
>
>              If you wish to abort the renice process, do one of the following depending on your progress:
>                  1) at the pid prompt, type an invalid number
>                  2) at the nice prompt, type <Enter> with no input
>                  3) at any prompt, type <Esc>
>```
r키를 누르면 Renice-a-Task로써 프로세스의 nice값을 변경할 수 있습니다. nice값은 프로세스의 우선순위를 결정하는 중요한 수치로써 
-20 ~ 19의 값의 범위를 가진다고 합니다.
nice 값이 작을수록 높은 우선순위를 지닌다고 하며 0이 기본값입니다.

한번 직접 top의 우선순위를 높혀보겠습니다.

<img width="748" height="188" alt="image" src="https://github.com/user-attachments/assets/607eff0e-1728-4af1-8a59-17b15bd4746f" />

여기서 r을 입력합니다.

<img width="745" height="188" alt="image" src="https://github.com/user-attachments/assets/f8306489-e5b1-4107-b2bd-507e7ad83ea1" />

그러면 pid를 입력하라는 창이 나옵니다.

<img width="728" height="181" alt="image" src="https://github.com/user-attachments/assets/2b894558-525d-421f-94ab-6a08822acd5b" />

적절한 top의 pid인 `7935`를 입력해줍니다.

<img width="728" height="183" alt="image" src="https://github.com/user-attachments/assets/8fd8ba07-46de-4f6c-820b-bc558b9a0aa0" />

재설정할 nice값을 입력하라는 창이나옵니다.

<img width="732" height="184" alt="image" src="https://github.com/user-attachments/assets/3a16d746-74a0-423f-9aa2-5dabdca69606" />

`-1`을 넣어주도록 하겠습니다.

<img width="736" height="193" alt="image" src="https://github.com/user-attachments/assets/efe23c84-8454-4295-9a7b-a7516b7abbb8" />

권한이 없다고 거부당했습니다.

※ root 권한이 없다면 우선순위를 기본값보다 높이는 것은 불가능하며, 이를 위해서는 `sudo top`을 통하여 root권한으로 top을 실행해야합니다.

그런데 root권한이 있는데도 거부당했네요

그럼 우선순위를 낮춰보겠습니다.

<img width="742" height="199" alt="image" src="https://github.com/user-attachments/assets/2861d861-f551-45ad-913c-590c351f722e" />

`1`을 넣어주었습니다.

<img width="737" height="201" alt="image" src="https://github.com/user-attachments/assets/e117d229-5e21-416e-9eac-d2264888cd0c" />

성공적으로 적용되어 디테일 영역의 top 프로세스의 NI값이 1로 변경되었습니다. 우선순위가 내려왔다고 볼 수 있습니다.

---

##### top 종료
top 명령어를 종료하는 키는 `q`입니다.
`q`를 누르면 즉시 top 명령어 상태를 빠져나올 수 있습니다.

---

---

## ps 명령어

<img width="270" height="87" alt="image" src="https://github.com/user-attachments/assets/76af4397-a16a-42ee-8875-eb304a2aa249" />

ps를 한번 쳐보면 이런 결과가 나옵니다.

top명령어의 기능중 하나인 현재 실행중인 프로세스를 표시하는 것 같습니다.
특이사항으로는 top은 계속 모니터링하지만 ps는 그 순간의 결과를 출력할 뿐입니다.

이번에도 아래의 명령어를 통해 사용방법을 얻어내 보겠습니다. 

```Shell
man ps > ps_manual.txt
```

Description의 일부분을 발췌해 보았습니다.

>```
>       ps displays information about a selection of the active processes.  If you want a repetitive update of the
>       selection and the displayed information, use top instead.
>```

> ps는 현재 활성화된 프로세스들의 정보를 선별하여 표시합니다. 만약 선택된 정보가 반복적으로 업데이트되는(실시간) 화면을 원한다면 ps 대신 top 명령어를 사용하십시오.

man 명령어에서도 실시간 업데이트되는 정보를 계속 보려면 top을 사용하라고 권장하네요.

>```
>-f     Do full-format listing.  This option can be combined with many other UNIX-style options to add
>              additional columns.  It also causes the command arguments to be printed.  When used with -L, the NLWP
>              (number of threads) and LWP (thread ID) columns will be added.  See the c option, the format keyword
>              args, and the format keyword comm.
>```

> `-f` 전체 형식으로 목록을 출력합니다. 이 옵션은 다른 유닉스 스타일의 옵션을 함께 조합하여 추가적인 속성을 추가할 수 있으며, 명령어 실행 시 입력한 인자(arguments)까지 모두 출력하게 만듭니다. -L 옵션(스레드 보기)과 함께 사용하면, NLWP(스레드 개수)와 LWP(스레드 ID) 열이 목록에 추가됩니다. c 옵션, 포맷 키워드 args, 포맷 키워드 comm 항목을 참조하여 차이점을 확인하십시오.

<img width="535" height="75" alt="image" src="https://github.com/user-attachments/assets/13689a50-ca83-4205-826d-730597fcdf46" />

`ps -f` 처럼 `-f` 인자를 넣어주면 좀더 자세한 결과를 추가하며, 다른인자와 함께 조합하여 추가적인 속성을 넣을 수 있다고 합니다.
`UID`, `PID`, `PPID` 등이 함께 표시됩니다.

`PPID`는 부모 프로세스 ID라고 합니다. 

>```
> -l     Long format.  The -y option is often useful with this.
>```

long format입니다. `-y`옵션과 주로 함께 사용됩니다.
우선순위와 관련된 PRI와 NI값을 확인할 수 있습니다.

`S`는 status 즉 상태를 의미하며 
       
* R : 실행중 혹은 실행할 수 있는 상태
* S : 대기상태 (20초 이상)
* I : 대기상태 (20초 이하)
* T : 작업 제어에 의해 정지된 상태
* D : 디스크 관련 대기 상태
* P : 페이지 관련 대기 상태
* X : 메모리 확보를 위한 대기 상태
* \> : 인위적으로 우선 순위가 높아진 상태
* Z : 좀비 프로세스

~~PS : escape \\를 입력하니까 \> 문자가 인용구로 사용되지 않고 작성이 가능하네요\~~~

<img width="645" height="77" alt="image" src="https://github.com/user-attachments/assets/69eb6656-3966-4b81-9db6-9f83df44d927" />

>```
>-e     Select all processes.  Identical to -A.
>```

모든 프로세스를 조회합니다.
-A명령어도 같은 기능이라고 합니다.
만약 이 옵션이 없다면 현재 사용자(shell)이 실행중인 프로세스만 보여준다고 합니다.

<img width="263" height="75" alt="image" src="https://github.com/user-attachments/assets/abc3c450-bf7e-43fc-a428-f1e61ce81cfe" />

아쉽지만 현재 다른 접속중인 쉘이 없어서 그냥 ps 명령어를 입력한 결과와 다른게 없습니다.
만약 월요일 온라인 수업에서 ssh를 통한 연결을 제대로 숙지한뒤 여유가 되면 시도해 보도록 하겠습니다.

```Shell
ps -elf
```
`-f`설명할때처럼 이와같이 여러인수를 한번에 입력하면 모든프로세스의 자세한 정보를 조합하여 조회할 수 있습니다.

<img width="776" height="79" alt="image" src="https://github.com/user-attachments/assets/2bb49baa-e768-45fa-86c0-b37c2e111065" />

---
---

## jobs 명령어

```shell
man jobs > jobs_manual.txt
```

이번에도 마찬가지로 위 명령어로 사용법을 얻어줍니다.

위 두 내용에 비해 내용이 짧습니다.

>```
>DESCRIPTION
>       The jobs utility shall display the status of jobs that were started in the current shell environment; see Sec-
>       tion 2.12, Shell Execution Environment.
>
>       When jobs reports the termination status of a job, the shell shall remove its process  ID  from  the  list  of
>       those ``known in the current shell execution environment''; see Section 2.9.3.1, Examples.
>
>```

> jobs 유틸리티는 현재 쉘 환경에서 시작된 작업(job)들의 상태를 표시합니다. (참조: 섹션 2.12 쉘 실행 환경)
> jobs 명령어가 어떤 작업의 종료 상태(끝났음, 실패함 등)를 보고하고 나면, 쉘은 "현재 쉘 실행 환경에 알려진 목록"에서 해당 작업의 프로세스 ID(PID)를 제거합니다.

결론만 말하면 jobs는 현제 쉘 환경에서만 실행중인 작업들을 표시하는 역할을 합니다.
그리고 딱한번만 job 명령어를 실행하기 전까지 완료된 작업을 보고해줍니다.

아래의 명령어가 있습니다.
```shell
sleep 5&
```
`sleep 5`를 백그라운드로 수행하라는 뜻으로 별의미 없이 5초간 대기하는 명령어입니다.

<img width="376" height="111" alt="image" src="https://github.com/user-attachments/assets/f607ac8b-b03d-417f-86a4-5bb88cea0804" />

위와같이 작업을 수행시킨뒤 jobs를 입력하면 5초간 대기합니다.

<img width="382" height="100" alt="image" src="https://github.com/user-attachments/assets/b0d29729-a71e-4d31-bd7d-0313925f7c51" />

5초가 경과된 후 다시 `jobs` 명령어를 실행한다면 

<img width="408" height="149" alt="image" src="https://github.com/user-attachments/assets/b9b46346-428d-44c7-842a-cfb1f678973d" />

Done 이라는 보고를 합니다.

<img width="406" height="96" alt="image" src="https://github.com/user-attachments/assets/d27634a1-152f-4acc-b51f-b3ff53f041a9" />

Done 이라는 보고가 완료된 후 jobs를 한번 더 입력해보면 완료 보고를 한 작업은 리스트에서 제거되어 더이상 보고되지 않는 모습입니다.

```
OPTIONS
       The  jobs  utility  shall conform to the Base Definitions volume of POSIX.1-2017, Section 12.2, Utility Syntax
       Guidelines.

       The following options shall be supported:

       -l        (The letter ell.) Provide more information about each job listed. This information shall include the
                 job number, current job, process group ID, state, and the command that formed the job.

       -p        Display only the process IDs for the process group leaders of the selected jobs.

       By  default,  the  jobs  utility shall display the status of all stopped jobs, running background jobs and all
       jobs whose status has changed and have not been reported by the shell.
```

> `-l` : 나열된 작업에 대해 더 많은 정보를 보여줍니다. 작업 번호, 현재 상태뿐만 아니라 프로세스 그룹 ID(사실상 PID) 등을 포함합니다.

> `-p` : 선택된 작업들의 프로세스 ID(PID)만 표시합니다.

<img width="432" height="116" alt="image" src="https://github.com/user-attachments/assets/5ac36343-847e-43ea-ac83-a93c0dec520b" />

실행해보면 `-l`을 입력시 pid만 앞에 붙여서 조회 `-p`를 입력시 프로세스 ID만 띡하고 나오는 모습입니다.

`man`에는 표시되지 않았지만 좀더 많은 옵션이 있습니다.
* `-r` : 실행중인 작업만 출력
* `-s` : 일시중지된 작업만 출력
* `-n` : 가장 최근에 상태가 변경된 작업만출력

---
---

## kill

>```
>DESCRIPTION
>       The default signal for kill is TERM.  Use -l or -L to list available signals.  Particularly useful signals in-
>       clude HUP, INT, KILL, STOP, CONT, and 0.  Alternate signals may be specified in three ways:  -9,  -SIGKILL  or
>       -KILL.  Negative PID values may be used to choose whole process groups; see the PGID column in ps command out-
>       put.  A PID of -1 is special; it indicates all processes except the kill process itself and init.
>```

> kill 명령어의 기본 신호는 TERM(Terminate)입니다.

> 특히 유용한 신호로는 다음과 같은 것들이 있습니다. `HUP` `INT` `KILL` `STOP` `CONT` `0`

> 신호를 지정할 때는 다음 세 가지 방법을 모두 쓸 수 있습니다. `-9` `-SIGNAL` `-KILL`

> PID 앞에 -를 붙이면 프로세스 그룹에 해당되는 모든 프로세스를 죽입니다.

> -1은 좀 특수한데, `init`프로세스를 제외한 모든 프로세스를 죽입니다.

아래는 유용한 신호와 그 기능을 정리한 정보입니다. 

|  신호    |   기능                                                 |
|:--------:|:------------------------------------------------------:|
| `HUB`    | Hang Up. 주로 설정 파일을 다시 읽게(Reload) 할 때 씀.    |
| `INT`    | Interrupt. 키보드 `Ctrl + C` 를 누른 것과 같음.         |
| `KILL`   | 강제 종료. 프로세스가 무시할 수 없음.                    |
| `STOP`   | 일시 정지. 프로세스를 메모리에 둔 채 멈춤.                |
| `CONT`   | 재시작(Continue). 멈춘(STOP) 프로세스를 다시 돌림.       |
| `0`      | 체크용. 실제 종료하진 않고 프로세스가 살아있는지 확인만 함.|


* `KILL` 명령어는 풀네임 `SIGKILL`, 신호번호 `-9` 로도 입력할 수 있다고 합니다.
* 만약 kill 명령어가 옵션없이 사용된다면 강제로 종료하지는 않고 종료신호 요청을 보내는 방식을 사용한다고 합니다.

<img width="370" height="114" alt="image" src="https://github.com/user-attachments/assets/bbb8c903-9ec0-4c3c-b8a8-d9449c84f65c" />

* 180초동안 sleep 명령을 수행시켰지만 `kill 118`(118은 pid) 명령을 접수받아 `jobs`명령어로 확인해보면 Terminate 된 모습을 확인할 수 있습니다.

※ 제 실력으로는 강제로 응답없는 프로그램을 만들기는 힘들어서 옵션들에 대한 실습은 생략하도록 하겠습니다.

※ 만약 프로세스 아이디 자리 앞에 %를 붙인다면 jobs에서 표기된 작업 번호로도 kill 명령어를 사용할 수 있습니다.

---
---
## 정리

* `tops` : 작업괸리자 처럼 현재 실행중인 모든 프로세스의 계속 업데이트되는 세부정보를 실시간으로 확인하며 바로 종료시키거나 우선순위를 변경할 수 있습니다.
* `ps` : 명령어가 입력된 순간의 프로세스들의 목록을 표시합니다.
* `jobs` : 현재 쉘에서 작업중인 작업들의 목록과 완료후 보고를 확인합니다.
* `kill` : PID를 입력하여 해당하는 프로세스를 종료시킵니다. option을 주면 강제로 종료시킬 수도 있습니다.
* tops명령어가 가장 복잡하며 다양한 기능을 가지고 있으며 다른 3개의 명령어의 기능을 어느정도 대체하거나 포함하고 있었습니다.

## 참고 자료

[tops 명령어](https://sabarada.tistory.com/146)

[ps 명령어](https://tigris-data-science.tistory.com/entry/Linux-ps-%EB%AA%85%EB%A0%B9%EC%96%B4)

[ps 명령어](https://co-no.tistory.com/entry/Linux-%ED%94%84%EB%A1%9C%EC%84%B8%EC%8A%A4-%EB%AA%A8%EB%8B%88%ED%84%B0%EB%A7%81%EC%9D%84-%EC%9C%84%ED%95%9C-%EC%9C%A0%EC%9A%A9%ED%95%9C-ps-%EB%AA%85%EB%A0%B9-%EC%98%88%EC%A0%9C)

[jobs 명령어](https://monkeybusiness.tistory.com/630)

[kill 명령어](https://eunji-study.tistory.com/14)
