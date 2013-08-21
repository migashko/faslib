//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_DETAIL_ASPECT_HELPER_HPP
#define FAS_AOP_DETAIL_ASPECT_HELPER_HPP

#include <fas/aop/group.hpp>
#include <fas/aop/forward.hpp>

#include <fas/aop/private/aspect_select.hpp>
#include <fas/aop/private/group_object.hpp>
#include <fas/aop/private/is_advice.hpp>
#include <fas/aop/private/is_alias.hpp>
#include <fas/aop/private/is_group.hpp>
#include <fas/aop/private/is_aspect.hpp>
#include <fas/aop/private/is_remover.hpp>
#include <fas/aop/private/is_forward.hpp>
#include <fas/aop/private/is_has_tag.hpp>
#include <fas/aop/private/tag_cast.hpp>
#include <fas/aop/private/target_cast.hpp>

#include <fas/algorithm/erase_if.hpp>
#include <fas/algorithm/transform_tail_if.hpp>
#include <fas/algorithm/transform_tail.hpp>
#include <fas/algorithm/transform.hpp>
#include <fas/algorithm/transform_if.hpp>
#include <fas/algorithm/unique_first_if.hpp>
#include <fas/algorithm/find_if.hpp>
#include <fas/algorithm/select.hpp>

#include <fas/mp/placeholders.hpp>
#include <fas/mp/a.hpp>
#include <fas/mp/p.hpp>

#include <fas/type_list/unique_first.hpp>
#include <fas/type_list/unique.hpp>
#include <fas/type_list/reverse.hpp>
#include <fas/type_list/merge.hpp>
#include <fas/type_list/tail.hpp>
#include <fas/type_list/head.hpp>
#include <fas/type_list/organize.hpp>


#include <fas/integral/not_equal_to.hpp>
#include <fas/integral/int_.hpp>

namespace fas{ namespace detail{

template<typename A>
struct aspect_helper
{
private:
  // Выбираем все адвайсы всех аспектов (любого уровня вложенности)
  // и строим плоский список элементов
  typedef typename aspect_select<A>::type flat_list_type;

  // Для каждого элемента типа remover перестраиваем хвост списка
  // из которого удаляються любые элементы с тегом, которым помечен remover.
  // Сам элемент remover в списке оставляем для того, чтобы при обращении
  // к такому элементу выдать ошибку advice_has_been_removed
  typedef typename transform_tail_if<
    // На вход плоский список без дополнительных преобразований
    flat_list_type,
    // На вход этой метафункции передаеться хвост основного списка, первым
    // элементом которого всегда будет remover.
    // На выходе - преобразованый спискок который заменяет текущий хвост основного списка
    merge<
      // оставляем голову списка ( элемент remover )
      head<_1>,
      // Удаляем все элементы с тегом перврго элемента remover из хвоста
      erase_if<
        // отсекаем голову (извлекаем хвост из входного списка)
        tail<_1>,
        // условие удаления (метафункция высшего порядка)
        // если элемент имеет тег и этот тег совпадает с тегом элемента головы
        a< is_has_tag< p<_1>, tag_cast< head< _1 > > > >
      >
    >,
    // применяем метафункцию только для элементов remover
    is_remover<_1>
  >::type net_list_type;

  // Заменяем все элементы group<-tag-,-tag-list-> на group_object<-tag->.
  // Список целей (-tag-list-) на данном этапе не нужен.
  // Т.к. группы могут определяться несколькими элементами group,
  // то после преобразования получим дубликаты элементов group_object<-tag->
  // в списке. Удаляем все дубликаты из списка (заодно и те элементы, которые
  // были внесены в аспект несколько раз намеренно или по недосмотру), оставляя
  // первое вхождение.
  // Это основной список, по которму будет осуществляться поиск
  typedef typename unique_first<
    typename transform_if<
      net_list_type,
      group_object< tag_cast< _1 > > ,
      is_group<_>
    >::type
  >::type common_list_type;

  // Удаляем из общего списка все элементы кроме тех, на базе которых
  // будет построена иерархия аспекта класса. Тип group_object<-tag->
  // останеться в списке (это обычный адвайс), а управляющие адвайсы
  // (alias, forward и remover) будут удалены
  typedef typename erase_if<
    common_list_type,
    not_< is_advice<_1> >
  >::type hierarchy_list_type;

  // Метафункция высшего порядка результатом выполнения которой,
  // будет метафункция сравнивающая тег элемента с тегом головы списка
  // ( is_has_tag< _1, -tag- > )
  typedef a< is_has_tag< p<_1>, tag_cast< head<_1> > > > equal_head_tag;

  // Формируем список состоящий только из элементов group, при этом элементы
  // с одинаковыми тегами объединяются в один. Списки целей всех таких элементов
  // объединяются в один общий список (с удалением дубликатов) и создается
  // новый элемент group, который вноситься в список, а остальные элементы удаляются
  typedef typename transform_tail<
    // Извлекаем из списка элементы group
    typename select_t<
      net_list_type,
      is_group
    >::type,

    // Объеденяем новый элемент group с хвостом списка, из которого убраны
    // старые элементы group
    merge<
      // Новый элемент group
      group<
        // с тегом как у первого элемента входного списка
        tag_cast< head< _1 > >,
        // удаляем дубликаты из общего списка целей
        unique_first<
          // Реверсируем список, чтобы список был порядке их добавления в аспект
          //reverse<
            // после трансформации список может быть "поломатым" - чиним его
            organize<
              // преобразум список из элеметов group в список списков целей
              // это не корректный список который нужно организовать
              transform<
                // извлекаем из списка нужные элементы group
                select< _1, equal_head_tag >,
                // для каждого элемента извлекаем список целей
                a< target_cast< p<_1> > >
              >  // transform
            >  // organize
          // > // reverse
        >  // unique
      >, // group
      // Удаляем все элементы с тегом, как у первого элемента в списке
      erase_if< _1, equal_head_tag >
    > // merge
  >::type native_group_list_type;

  typedef typename select<
    native_group_list_type,
    is_group<
      find_if<
        flat_list_type,
        a< is_has_tag< p<_1>, tag_cast<_1> > >
      >
    >
  >::type group_list_type;

public:
  typedef common_list_type common_list;
  typedef hierarchy_list_type hierarchy_list;
  typedef group_list_type group_list;
};

}}

#endif
