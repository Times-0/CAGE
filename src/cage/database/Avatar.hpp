#ifndef CAGE_DATABASE_PUBLIC_AVATAR_H
#define CAGE_DATABASE_PUBLIC_AVATAR_H


#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace cage {
namespace database {
	namespace Avatar_ {

		struct Id {
			struct _alias_t {
				static constexpr const char _literal[] = R"("id")";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T id;
						T &operator()() { return id; }
						const T &operator()() const { return id; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::must_not_insert, sqlpp::tag::must_not_update>;
		};

		struct Nickname {
			struct _alias_t {
				static constexpr const char _literal[] = R"("nickname")";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T nickname;
						T &operator()() { return nickname; }
						const T &operator()() const { return nickname; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};
	} // namespace Avatar_

	struct Avatar : sqlpp::table_t<Avatar,
				Avatar_::Id,
				Avatar_::Nickname> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = R"("public"."Avatar")";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T Avatar;
					T &operator()() { return Avatar; }
					const T &operator()() const { return Avatar; }
				};
		};
	};
} // namespace database
} // namespace cage

#endif
