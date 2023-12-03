from telegram import (
    InlineKeyboardButton,
    InlineKeyboardMarkup,
    Update,
)
from telegram.ext import (
    ApplicationBuilder,
    CallbackQueryHandler,
    ContextTypes,
    MessageHandler,
    filters,
)


from iffbot.storage import Storage

with open(".token") as f:
    token = f.read().strip()

storage = Storage()


async def game_command(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    story = storage.get_user_story(context._chat_id)
    message = await story.do(update.message.text)
    keyboard = [
        [
            InlineKeyboardButton(
                story.translator.translate("Translate"), callback_data="/traslate"
            )
        ],
    ]
    reply_markup = InlineKeyboardMarkup(keyboard)
    await update.message.reply_text(message, reply_markup=reply_markup)


async def translate(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:
    story = storage.get_user_story(context._chat_id)
    query = update.callback_query
    await query.answer()
    await query.message.reply_text(story.translator.translate(query.message.text))


def main():
    app = ApplicationBuilder().token(token).build()
    app.add_handler(MessageHandler(filters.ALL, game_command))
    app.add_handler(CallbackQueryHandler(translate))
    app.run_polling()


if __name__ == "__main__":
    main()
