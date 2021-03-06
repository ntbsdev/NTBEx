# Обзор
Модель децентрализованной торговой платформы, предложенная в этом техническом документе, представляет собой попытку описать операционную модель распределенной биржи, которая отличается от существующих бирж цифровых активов. На данный момент торговая платформа NTBEx все еще находится в стадии разработки, и ее концепции дизайна и алгоритмы могут постоянно обновляться и изменяться. Хотя в этой статье содержится самая свежая информация о торговой платформе NTBEx, она не очень всеобъемлющая и полная, и команда разработчиков может продолжать вносить коррективы и обновления.
Мы будем участвовать в обсуждениях с техническими экспертами, юристами и пользователями сообщества в процессе продвижения проекта и внесем изменения в содержание белой книги на основе дальнейшей оптимизации.
# Резюме
Появление EOS RAM успешно подтвердило возможность реализации децентрализованных транзакций на основе EOS с помощью протокола bancor. Основываясь на этом, мы разработали операционную модель торговой платформы NTBEx, надеясь решить болевые точки существующей торговой платформы с помощью этого видения и принести пользу всей цепочке индустрии цифровых активов БЛОКЧЕЙНА.
NTBEx - это децентрализованная и открытая торговая платформа, основанная на EOS. Ее главной особенностью является то, что она полностью открыта и прозрачна. Торговая платформа NTBEx реализована с использованием смарт-контрактов протокола Bancor, что отлично решает проблему недостаточной ликвидности существующих цифровых валют, а также может решить проблему эффективности существующих торговых платформ. В будущем торговая платформа NTBEx также будет осуществлять межцепочечные транзакции и полностью реформировать существующую торговую модель.
Открытая торговая платформа NTBEx принимает форму совета для управления платформой. Совет директоров был избран голосованием NTBToken после завершения обмена токенами, и членами совета директоров являются 7. В первой половине основания торговой платформы NTBEx команда основателей обладала всеми полномочиями по управлению, а через полгода эти полномочия были переданы сообществу.
# 1. Предыстория проекта
## (1) Возможности цифровых активов
С технологическим развитием Интернета и блокчейна цифровые активы вошли в кругозор людей и даже стали частью повседневной жизни людей.
Цифровые активы оказывают глубокое влияние на все аспекты экономики и общества, особенно на финансовую систему. Логично, что может быть несколько результатов: во-первых, изменяется структура валюты и увеличивается валютный мультипликатор; во-вторых, спрос на физическую валюту продолжает снижаться, а скорость взаимной конвертации финансовых активов ускоряется; в-третьих, скорость обращения валюты улучшилась. Измеримая степень и основа анализа больших данных более прочны, что способствует лучшему расчету общей суммы валюты и анализу структуры валюты; в-четвертых, снизить затраты KYC и AML и повысить эффективность регулирования; в-пятых, обеспечить эффективный общая финансовая среда и стимулирование финансовых инноваций.
С 2014 года центральный банк организовал отраслевых экспертов для создания исследовательской группы по цифровым активам для проведения углубленных исследований структуры выпуска и функционирования цифровой валюты, ключевых технологий цифровых активов, среды выпуска и обращения цифровых активов, правовых проблем, с которыми сталкиваются цифровые активы, и влияние цифровых активов на экономическую и финансовую систему, взаимосвязь между законными цифровыми активами и частными цифровыми активами, а также опыт выпуска иностранных цифровых активов и т. Д. Достигли поэтапных результатов.
В будущем цифровые активы столкнутся с более широкими рыночными возможностями. Использование возможностей цифровых валют равносильно использованию будущих возможностей для бизнеса.
## (2) Текущее состояние биржи
Биржи, можно сказать, являются самым любимым и ненавистным существованием в валютном круге. Связывая монеты и цепочки, проекты могут реализовывать ценность с помощью бирж, а технологии могут быть реализованы на биржах. Это самый центральный центр ценности в экосистеме блокчейна. Однако в настоящее время биржи, как правило, имеют такие недостатки, как уязвимости в системе безопасности, нечеткие стандарты, отсутствие надзора и незаконные операции. Эти проблемы необходимо срочно решить, если индустрия цифровых активов хочет добиться больших успехов.
### 1．Низкая ликвидность торговых инструментов
На рынке криптовалют существуют десятки тысяч торговых инструментов, и они растут с каждым днем, и инструменты, перечисленные на различных биржах, также противоречивы. С увеличением проектов количество бирж на торговой платформе также увеличивается день ото дня. В качестве примера можно привести Binance, ветеранскую головную биржу, по состоянию на июль 2018 года насчитывалось до 300 торговых пар. По известным причинам большинство платформ имеют неудобные депозиты. В случае нехватки средств для входа слишком много торговых пар распыляют биржевые средства на платформе, что приводит к недостаточной глубине торговых пар. В то же время средства пользователей, как правило, стекаются в новые проекты. В торговых парах, которые долгое время находятся в сети, пользователям сложно покупать и продавать, и торговая платформа попадет в порочный круг низкой ликвидности.
### 2．Высокий порог для включения в список
Крупные биржи часто подвергаются критике со стороны инвесторов за их высокие листинговые сборы и непрозрачность. Команда проекта собирает средства для развития маркетинга и технологий посредством частного размещения и публичных предложений. Большая часть средств, привлеченных для развития маркетинга и технологий, должна быть использована для оплаты высоких листинговых сборов. Эти сборы в конечном итоге будут распределены между инвесторами, что приведет к сокращению прибыли инвесторов.
### 3．Не в состоянии доказать свою невиновность
Торговая платформа всегда была наиболее критикуемой из существующих валютных кругов, и недоверие пользователей к платформе растет день ото дня, и даже были случаи, когда многие пользователи отправлялись на биржи, чтобы защитить свои права. Такого рода недоверие в конечном счете вызвано непрозрачностью биржевых данных. Больше всего торговым платформам нужно доказать свою невиновность.
### 4．Частые проблемы с безопасностью
Проблемы безопасности всегда были самой большой скрытой опасностью бирж. В дополнение к проблемам безопасности самой платформы, криптовалютные биржи также сильнее всего пострадали от хакерских атак.
В декабре 2017 года южнокорейская биржа Youbit была взломана, и 17% ее активов были украдены. Веб-сайт в конечном итоге закрыл биржу и объявил о банкротстве; 25 января 2018 года был взломан японский Coincheck, и клиенты биржи потеряли 530 миллионов долларов США в криптовалютных активах; 7 марта 2018 года Binance подозревался во взломе. Хакеры увеличили стоимость Биткоина в 110 раз, в результате чего Биткоин падал два дня подряд, а его рыночная стоимость упала на 15%.
Проблемы безопасности привели к прямым потерям активов пользователей, но многие биржи не могут полностью решить эти проблемы.
№ 2. Видение платформы
Торговая платформа NTBEx является первой в мире распределенной биржей, которая выступает за полную децентрализацию. Она надеется создать эффективную и прозрачную платформу для торговли активами, соответствующую духу блокчейна с помощью смарт-контрактов и сетевого управления, обслуживающую все проекты цифровых активов и пользователей цифровых валютных активов по всему миру, и способствующую прогрессу и развитию индустрии блокчейна.
#3. Преимущества платформы
Миссия NTBEx заключается в создании прозрачной торговой среды для инвесторов в цифровые активы, торговле цифровыми активами и управлении ими. Самой большой особенностью платформы является прозрачность, которая может обеспечить открытость и прозрачность каждого заказа, а все активы пользователей торгуются по цепочке, которая понятна и поддается проверке.В то же время отвечайте требованиям соблюдения нормативных требований в области безопасности, аудита, отчетности, анализа и т.д. Самым безопасным и эффективным способом.
## (1) Огромная база пользователей
Торговая платформа NTBEx open доступна и используется в качестве точки входа через все кошельки EOS, прекрасно наследуя огромную базу пользователей системы EOS. Она поддерживает все транзакции токенов с EOS в цепочке EOS на ранней стадии и будет поддерживать транзакции между цепочками во всех валютах, таких как BTC и NTBExH в будущем.
## (2) Полностью открытый и прозрачный
Все транзакции на торговой платформе NTBEx автоматически совершаются с помощью алгоритма смарт-контракта bancor, все данные раскрываются в режиме реального времени, и вся информация полностью симметрична и прозрачна. Пользователи могут запрашивать данные в цепочке в режиме реального времени через браузер блоков, избегая ряда проблем с доверием, вызванных непрозрачностью.
## (3) Открытая платформа
Опираясь на технологию БЛОКЧЕЙНА и концепцию оптимизации токенов, открытая торговая платформа NTBEx станет первой торговой платформой в мире, которая будет отстаивать открытость и автономию. Все коды имеют открытый исходный код, все интерфейсы открыты, и все существующие торговые платформы могут быть легко интегрированы. И наслаждайтесь прибылью, получаемой от торговли на своей платформе.
## (4) Намного опережает график
Официальная версия запустила закрытое бета-тестирование, и скоро будут открыты официальные транзакции. Все токены на базе EOS будут открыты для торговых пар EOS в течение 50 дней, и все сторонние кошельки будут легко доступны.
## (5) Технология, лежащая в основе EOS
** Высокий TPS**: Механизм DPOS EOS прошел высокочастотное тестирование, и TPS может достигать более 3000. В будущем он может быть расширен до миллиона уровней в соответствии с планами. 
** Функция обновления смарт-контрактов**: Кроме того, смарт-контракты EOS могут быть обновлены в любое время, чтобы гарантировать непрерывное итеративное обновление будущих функций.
** Способность к самовосстановлению**: Ошибок в коде избежать невозможно. Ужасно, что смарт-контракты не могут исправить, когда они сталкиваются с ошибками. EOS отлично поддерживает функцию восстановления кода. В случае хакерской атаки убытки также могут быть сведены к минимуму с помощью основного арбитражного форума EOS (ECAF).
** Конституционные ограничения**: EOS использует модель управления по цепочке. Все участники связаны конституцией и могут быть заморожены после совершения зла. Стоимость совершения зла в цепочке высока, а мотивация совершения зла не очевидна.
** Низкая стоимость связи**: Внутри и за пределами общедоступной сети EOS созданы распределенные приложения и механизм обмена сообщениями между цепочками, позволяющие приложениям беспрепятственно взаимодействовать друг с другом не только для связи друг с другом, но и для предоставления услуг друг другу. Это преимущество, не имеющее аналогов среди других платформ.

## (6) Поддержка ликвидности
Протокол Bancor представляет техническое решение для решения этой проблемы с использованием смарт-контрактов на основе блокчейна и резервных валют. Независимо от того, есть покупатели или нет, смарт-контракты автоматически покупаются и продаются с помощью определенного алгоритма, и алгоритм bancor может автоматически гарантировать ликвидность.
#4. Инновации и новаторский Банкор2.0
Выше мы уже объяснили преимущества и характеристики алгоритма bancor. Благодаря непрерывному повторению платформы и постоянному исследованию технической команды мы считаем, что платформа нуждается в инновациях и реформировании с точки зрения технологий. Мы прошли этап NTBEx1.0 с низкой стабильностью и несовершенным пользовательским интерфейсом в протоколе bancor и перешли на этап Bancor2.0 с пользовательским интерфейсом в качестве ядра. Это также совершенно новое изменение и опыт для нашей платформы NTBEx.
То, что мы хотим атаковать Bancor2.0, — это улучшить пользовательский интерфейс NTBEx и стать ведущей в отрасли платформой распределенной торговли.
Самой большой особенностью соглашения Bancor является то, что цена определяется открыто и прозрачно в соответствии с реальной формулой спроса и предложения, и не будет обмена, покупки и продажи поддельных монет; и нет связи с комиссией, не зависит от ликвидности, и нет контрагента. Если вы хотите покупать и продавать, вы можете торговать в любое время, и не будет неловкой ситуации, когда вы хотите купить, но никто не продает его.
## (1) Проблемы с соглашением Bancor
В какой-то степени соглашение Bancor достаточно совершенное, но все еще существуют некоторые неизбежные проблемы.
Во-первых, хотя пользователям не нужно беспокоиться о глубине сделок, если резервов недостаточно, сверхкрупные инвесторы могут легко контролировать цену определенной торговой пары, которая может легко попасть в олигархическое равновесие.
Во-вторых, поскольку обмены на блокчейне осуществляются 24 часа в сутки, отсутствие ссылки на комиссию означает, что пользователям необходимо следить за ними в течение 24 часов, что также означает, что в случае возникновения экстремальной ситуации это приведет к сокращению активов пользователя за короткий промежуток времени.
В-третьих, существует высокая вероятность того, что участник проекта по соглашению Bancor не будет положительно мотивирован. Когда недостаточно зрелый токен участника проекта указан на торговой платформе, он может быть продан. В худшем случае цена токена бесконечно близка к 0. В это время участник проекта чувствует себя злонамеренным на рынке и окажет определенное негативное влияние на ход всего проекта.
Основываясь на вышесказанном, биржа NTBEx предложила эпохальный Bancor 2.0. Он может осуществлять эффективный перевод и использование средств на бирже NTBEx и пользоваться удобством и скоростью традиционных обменов.
## (2) У Bancor2.0 больше преимуществ
### 1．Открытый резерв
Мы откроем пул управления резервными фондами. Любой желающий может вложить свои свободные средства в пул управления по текущей цене и в определенной пропорции. Вы будете наслаждаться доходом от комиссионных за обработку транзакций, приносимым этой частью средств, чтобы реализовать эффективное использование активов и обеспечить быстрый и удобный БЛОКЧЕЙН- высококачественный скрытый продукт управления капиталом. Это также после того, как FCOIN предложил транзакционный майнинг, обмен NTBEx (etdac.io) Предлагать новые суперсовременные продукты.
### 2．Механизм отложенных ордеров на комиссию в режиме онлайн
Bancor 2.0, предложенный NTBEx, также позволяет пользователям выполнять операции с отложенными ордерами. Например, цена EOS теперь составляет 100 юаней. С помощью традиционного механизма Bancor вы можете покупать или продавать только по текущей цене. В Bancor 2.0 вы можете установить 90 юаней для покупки или 110 юаней для продажи, что очень удобно для пользователей.
### 3．Положительные стимулы для участников проекта
В этом механизме некоторые высококачественные участники проекта, которые еще не были обнаружены, могут продемонстрировать здесь свои навыки, и привлеченные средства могут быть эффективно использованы. В то же время это может гарантировать, что участник проекта продолжит разработку производных на основе этого проекта, а также может обеспечить будущую стабильность всего проекта.
#5. Сравнение децентрализованных бирж
В настоящее время одна за другой появилось множество децентрализованных бирж, и наиболее влиятельными из них являются Newdex, DEXEOS, Bytetrade и NTBExdac. Далее мы проведем сравнение с точки зрения пользовательского опыта, чтобы помочь каждому понять различия между NTBEx и другими децентрализованными транзакциями.
dКак видно из приведенной выше таблицы, самыми большими преимуществами NTBEx являются торговая модель и преимущества открытого исходного кода.
Алгоритм Bancor обладает естественными преимуществами по сравнению с традиционными торговыми моделями, особенно в непопулярных валютах. Самая примитивная и важная ценность валюты заключается в том, что она удобна в обращении и быстро циркулирует. Если будет потрачено ненужное время на ожидание нужного объекта транзакции, его стоимость значительно снизится. Алгоритм Bancor представляет собой асинхронный ценовой механизм, поэтому он может идеально решить вышеуказанные болевые точки.
Согласно характеристикам алгоритма Bancor, ваша транзакция осуществляется не с людьми, у которых есть потребности в транзакциях, а с людьми. Например, цена оперативной памяти EOS, которую вы сейчас видите, устанавливается не из-за торговых потребностей других людей, а по цене, рассчитанной самой системой в соответствии с формулой. То, что вы покупаете в данный момент, не имеет ничего общего с тем, что кто-то продает на противоположной стороне экрана. Независимо от того, хотят другие продавать это или нет, вы можете купить в системе то, что хотите.
Видно, что для этих децентрализованных бирж, созданных на основе основной цепочки EOS, разумнее использовать алгоритм Bancor.
Скорость транзакций: Основная сеть Ethereum имеет скорость менее 20 TPS. Поэтому опыт децентрализованных бирж на основе Ethereum в прошлом подвергался критике. Фактическое измерение TPS основной сети EOS превысило 3700, что в принципе может быть подтверждено за считанные секунды, и его опыт совершенно не имеет себе равных среди децентрализованных бирж в прошлом.
Плата за обработку: Децентрализованные биржи, основанные на Ethereum, должны сжигать не менее 3% ГАЗА от перевода на биржу, сопоставления и вывода. Это не включает плату за обработку, взимаемую биржей, что еще более неприемлемо, когда сеть Ethereum перегружена. Неприемлемо. Децентрализованная торговая платформа NTBEx требует только взимания платы за платформу, и NTBEx открыта для всех сторонних кошельков EOS, а код имеет открытый исходный код. Плата за обработку транзакций, генерируемая на платформе, определяется подключенным кошельком, а плата за обработку отправляется непосредственно на сторонний кошелек. Взимаемая плата за обработку полностью определяется рынком. В условиях полной рыночной конкуренции плата за обработку платформы NTBEx должна быть относительно справедливой.
Аспект прошлого опыта: В прошлом децентрализованным биржам требовалось импортировать закрытые ключи в Scatter, и существовал риск утечки закрытых ключей.NTBEx можно использовать непосредственно на кошельке, что очень удобно и безопасно.
#6. Распределенное управление сообществом
Распределенная автономная организация - это организационная форма, реализующая распределенность и автономию. Это дизайн, наиболее близкий к духу блокчейна.
Конечной целью NTBEx является достижение распределенного управления сообществом. Команда основателей децентрализована в области технологий и управления, а продвижение, принятие решений и управление сообществом также будут децентрализованы. Первоначальное намерение платформы состоит в том, чтобы все участники Et участвовали в процессе управления, а процесс предложения, обсуждения и принятия решений был открытым и прозрачным.
Для достижения этой цели команда основателей передаст право на закрытый ключ Совету директоров через полгода, и в это время платформа осуществит полное децентрализованное управление. Совет директоров несет единоличную ответственность за вопросы платформы, такие как взимание платы за обработку, размер взимаемой платы за обработку и стандарты листинга для последующих транзакций между цепочками определяются сообществом.
Торговая платформа NTBEx будет реализовывать дух блокчейна и развиваться в направлении распределенного управления. Владельцы NTBToken имеют право управлять, и все транзакции на платформе определяются управлением сообщества.
№7. Модель Прибыли
## (1) Комиссия за транзакцию
На торговой платформе NTBEx все токены на основе EOS могут быть предоставлены на ранней стадии, а торговые пары всех валют в мире блокчейна могут быть предоставлены даже на более поздней стадии. Спрос очень огромен, и генерируемые комиссионные за транзакции будут очень значительными.
## (2) Выпуск NTBToken
NTBToken - это монета платформы, выпущенная торговой платформой NTBEx. Владельцы NTBToken могут участвовать в голосовании и дивидендах.
## (3) Контрактные фьючерсы
Проценты и комиссионные за обслуживание транзакций, понесенные по контрактным фьючерсным кредитам.
№8. Партнерский план
Партнер по каналу связи：
Его можно бесплатно подключить к интерфейсу API платформы NTBEx, и все комиссии за транзакции автоматически выплачиваются на счет разработчика кошелька в полном объеме через смарт-контракты.
#9. Модель токена
## (1) Что такое NTBToken?
NTBToken является доказательством справедливости торговой платформы NTBEx. Объем выпуска должен быть определен и никогда не будет выпущен снова.
## (2) Общий объем выпуска
Общая сумма выпущенных NTBToken составляет 600 миллионов долларов.
## (3) Описание прав и интересов NTBToken
### 1．Выкупить и уничтожить
100% прибыли биржи автоматически выкупается и уничтожается с помощью смарт-контрактов.
### 2．Proof of Stake
Токен используется в качестве распространяемого зашифрованного цифрового подтверждения доли, NTBToken является Proof of Stake доли сообщества NTBEx, а владельцы NTBToken могут участвовать в управлении сообществом.
### 3．Управление сообществом
Владельцы NTBToken имеют право управлять сообществом. Как сообщество распределенного управления, члены сообщества голосуют (каждый человек может проголосовать за 1 голос), чтобы избрать 7 членов правления. После того как платформа будет стабильной в течение полугода, дела сообщества будут переданы от команды основателей совету директоров.
№10. Инструкции по сбору средств



#11. О нас
Адрес кошелька с открытым исходным кодом: https://github.com/ntbsdev/кошелек 
Адрес смарт-контракта биржи: https://github.com/ntbsdev/NTBEx 
Адрес официального веб-сайта:http://1rus.com 
Свяжитесь с нами: https://t.me/ntbmine

№12. Дорожная карта проекта
Шаг 1 2018.8.1 Транзакция оперативной памяти 
Шаг 2 2018.8.15 Торговля на основе токенов EOS (начало закрытого бета-тестирования) 
Шаг 3 2018.11 Поддержка транзакций между цепочками, таких как BTC и NTBEx 
Шаг 4 2019 года. 1 квартал Спотовая торговля с привлечением заемных средств 
Шаг 5 2019 года. Сделка по контракту в 1 квартале 


