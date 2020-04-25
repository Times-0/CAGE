#ifndef CAGE_DATABASE_PUBLIC_USER_H
#define CAGE_DATABASE_PUBLIC_USER_H


#include <sqlpp11/table.h>
#include <sqlpp11/char_sequence.h>
#include <sqlpp11/column_types.h>

namespace cage {
namespace database {
	namespace User_ {

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

		struct Username {
			struct _alias_t {
				static constexpr const char _literal[] = R"("username")";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T username;
						T &operator()() { return username; }
						const T &operator()() const { return username; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::varchar, sqlpp::tag::require_insert>;
		};

		struct Registration {
			struct _alias_t {
				static constexpr const char _literal[] = R"("registration")";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T registration;
						T &operator()() { return registration; }
						const T &operator()() const { return registration; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::time_point>;
		};

		struct Auth {
			struct _alias_t {
				static constexpr const char _literal[] = R"("auth")";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T auth;
						T &operator()() { return auth; }
						const T &operator()() const { return auth; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::can_be_null>;
		};

		struct Avatar {
			struct _alias_t {
				static constexpr const char _literal[] = R"("avatar")";
				using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
				template<typename T>
					struct _member_t {
						T avatar;
						T &operator()() { return avatar; }
						const T &operator()() const { return avatar; }
					};
			};

			using _traits = ::sqlpp::make_traits<::sqlpp::integer, sqlpp::tag::can_be_null>;
		};
	} // namespace User_

	struct User : sqlpp::table_t<User,
				User_::Id,
				User_::Username,
				User_::Registration,
				User_::Auth,
				User_::Avatar> {
		using _value_type = sqlpp::no_value_t;
		struct _alias_t {
			static constexpr const char _literal[] = R"("public"."User")";
			using _name_t = sqlpp::make_char_sequence<sizeof(_literal), _literal>;
			template<typename T>
				struct _member_t {
					T User;
					T &operator()() { return User; }
					const T &operator()() const { return User; }
				};
		};
	};
} // namespace database
} // namespace cage

#endif
